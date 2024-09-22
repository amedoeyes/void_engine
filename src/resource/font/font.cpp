#include "void_engine/resource/font/font.hpp"

#include "void_engine/resource/font/glyph.hpp"
#include "void_engine/resource/texture/enums.hpp"

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <freetype/freetype.h>
#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/ext/vector_uint2.hpp>
#include <hb-ft.h>
#include <hb.h>
#include <iterator>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace void_engine::resource::font {

Font::Font(
	FT_Library ft, const std::filesystem::path& path, unsigned int size, glm::uvec2 atlas_size
) :
	_ft(ft),
	_size(size),
	_atlas_size(atlas_size) {
	_faces.push_back(load_font(path, _size));
	_fonts.push_back(hb_ft_font_create(_faces.back(), nullptr));
	_texture.set_texture_storage_2d(1, resource::TextureInternalFormat::r8, _atlas_size);
	_texture.set_min_filter(resource::TextureMinFilter::linear);
	_texture.set_mag_filter(resource::TextureMagFilter::linear);
	_texture.set_wrap_s(resource::TextureWrap::clamp_to_edge);
	_texture.set_wrap_t(resource::TextureWrap::clamp_to_edge);
}

Font::Font(
	FT_Library ft, std::span<const std::byte> data, unsigned int size, glm::uvec2 atlas_size
) :
	_ft(ft),
	_size(size),
	_atlas_size(atlas_size) {
	_faces.push_back(load_font(data, _size));
	_fonts.push_back(hb_ft_font_create(_faces.back(), nullptr));
	_texture.set_texture_storage_2d(1, resource::TextureInternalFormat::r8, _atlas_size);
	_texture.set_min_filter(resource::TextureMinFilter::linear);
	_texture.set_mag_filter(resource::TextureMagFilter::linear);
	_texture.set_wrap_s(resource::TextureWrap::clamp_to_edge);
	_texture.set_wrap_t(resource::TextureWrap::clamp_to_edge);
}

Font::~Font() {
	for (auto* font : _fonts) {
		hb_font_destroy(font);
	}
	for (auto* face : _faces) {
		FT_Done_Face(face);
	}
}

void Font::add_fallback(const std::filesystem::path& path) {
	FT_Face face = load_font(path, _size);
	_faces.push_back(face);
	_fonts.push_back(hb_ft_font_create(face, nullptr));
}

void Font::add_fallback(std::span<const std::byte> data) {
	FT_Face face = load_font(data, _size);
	_faces.push_back(face);
	_fonts.push_back(hb_ft_font_create(face, nullptr));
}

auto Font::get_glyphs(std::u32string_view text) const -> std::vector<Glyph> {
	std::vector<Glyph> glyphs;
	glyphs.reserve(text.size());
	unsigned int font_index = 0;
	std::u32string sub_text;
	for (auto c : text) {
		for (size_t i = 0; i < _fonts.size(); ++i) {
			unsigned int glyph_index = 0;
			hb_font_get_nominal_glyph(_fonts[i], c, &glyph_index);
			if (glyph_index == 0) {
				continue;
			}
			if (i != font_index) {
				if (!sub_text.empty()) {
					std::ranges::move(get_glyphs(font_index, sub_text), std::back_inserter(glyphs));
					sub_text.clear();
				}
				font_index = i;
			}
			sub_text += c;
			break;
		}
	}
	if (!sub_text.empty()) {
		std::ranges::move(get_glyphs(font_index, sub_text), std::back_inserter(glyphs));
	}
	return glyphs;
}

auto Font::get_texture() const -> const resource::Texture& {
	return _texture;
}

auto Font::get_line_height() const -> unsigned int {
	return _faces[0]->size->metrics.height / 64;
}

auto Font::load_font(const std::filesystem::path& path, unsigned int size) -> FT_Face {
	FT_Face face = nullptr;
	const int result = FT_New_Face(_ft, path.string().c_str(), 0, &face);
	if (result != 0) {
		assert(false && "Failed to load font");
	}
	FT_Set_Pixel_Sizes(face, 0, size);
	return face;
}

auto Font::load_font(std::span<const std::byte> data, unsigned int size) -> FT_Face {
	FT_Face face = nullptr;
	const int result = FT_New_Memory_Face(
		_ft, std::bit_cast<unsigned char*>(data.data()), static_cast<long>(data.size_bytes()), 0, &face
	);
	if (result != 0) {
		assert(false && "Failed to load font");
	}
	FT_Set_Pixel_Sizes(face, 0, size);
	return face;
}

auto Font::get_glyphs(unsigned int index, std::u32string_view text) const -> std::vector<Glyph> {
	std::vector<Glyph> glyphs;
	glyphs.reserve(text.size());
	hb_buffer_t* buffer = hb_buffer_create();
	hb_buffer_clear_contents(buffer);
	hb_buffer_add_utf32(buffer, std::bit_cast<const uint32_t*>(text.data()), -1, 0, -1);
	hb_buffer_guess_segment_properties(buffer);
	hb_shape(_fonts[index], buffer, nullptr, 0);
	unsigned int glyph_count = 0;
	hb_glyph_info_t* glyph_info = hb_buffer_get_glyph_infos(buffer, &glyph_count);
	for (unsigned int k = 0; k < glyph_count; ++k) {
		glyphs.push_back(get_glyph(index, glyph_info[k].codepoint));
	}
	hb_buffer_destroy(buffer);
	return glyphs;
}

auto Font::get_glyph(unsigned int index, unsigned int codepoint) const -> const Glyph& {
	constexpr unsigned int padding = 1;
	auto [it, success] = _glyphs.try_emplace(index << 16u | codepoint);
	if (success) {
		FT_Face face = _faces[index];
		const int result = FT_Load_Glyph(face, codepoint, FT_LOAD_RENDER);
		if (result != 0) {
			assert(false && "Failed to load glyph");
		}
		const glm::uvec2 bitmap_size = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
		if (_next_glpyh_position.x + bitmap_size.x + padding > _atlas_size.x) {
			_next_glpyh_position.x = 0.0f;
			_next_glpyh_position.y += _max_glyph_height;
			_max_glyph_height = 0.0f;
		}
		if (_next_glpyh_position.y + bitmap_size.y + padding > _atlas_size.y) {
			assert(false && "Font atlas is too small");
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		_texture.set_sub_image_2d(
			0, _next_glpyh_position, bitmap_size, resource::TextureFormat::r, face->glyph->bitmap.buffer
		);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		it->second = {
			.codepoint = codepoint,
			.size = bitmap_size,
			.bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top},
			.advance = glm::vec2(face->glyph->advance.x, face->glyph->advance.y) * 0.015625f,
			.uv_position = glm::vec2(_next_glpyh_position) / glm::vec2(_atlas_size),
			.uv_size = glm::vec2(bitmap_size) / glm::vec2(_atlas_size)
		};
		_next_glpyh_position.x += bitmap_size.x + padding;
		_max_glyph_height = glm::max(_max_glyph_height, bitmap_size.y + padding);
	}
	return it->second;
}

} // namespace void_engine::resource::font
