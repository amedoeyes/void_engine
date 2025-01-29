module;

#include <cassert>
#include <freetype/freetype.h>
#include <hb-ft.h>
#include <hb.h>

module void_engine.resources;

import glm;
import std;

namespace void_engine::resources {

Font::Font(const std::filesystem::path& path, std::int32_t size) : _size(size) {
	if (_instance_count == 0) {
		const auto result = FT_Init_FreeType(&_ft);
		assert(result == 0 && "Failed to initialize FreeType");
	}
	++_instance_count;
	const auto result = FT_New_Face(_ft, path.string().c_str(), 0, &_face);
	assert(result == 0 && "Failed to load font");
	FT_Set_Pixel_Sizes(_face, 0, _size);
	_font = hb_ft_font_create(_face, nullptr);
}

Font::Font(std::span<const std::byte> data, std::int32_t size) : _size(size) {
	if (_instance_count == 0) {
		const auto result = FT_Init_FreeType(&_ft);
		assert(result == 0 && "Failed to initialize FreeType");
	}
	++_instance_count;
	const auto result = FT_New_Memory_Face(
		_ft, std::bit_cast<unsigned char*>(data.data()), static_cast<long>(data.size_bytes()), 0, &_face
	);
	assert(result == 0 && "Failed to load font");
	FT_Set_Pixel_Sizes(_face, 0, _size);
	_font = hb_ft_font_create(_face, nullptr);
}

Font::~Font() {
	hb_font_destroy(_font);
	FT_Done_Face(_face);
	--_instance_count;
	if (_instance_count == 0) {
		FT_Done_FreeType(_ft);
	}
}

auto Font::get_line_height() const -> float {
	return static_cast<float>(_face->size->metrics.height) / 64.0f;
}

auto Font::glyphs(std::string_view text) const -> std::vector<Glyph> {
	auto glyphs = std::vector<Glyph>();
	glyphs.reserve(text.size());
	auto* buffer = hb_buffer_create();
	hb_buffer_clear_contents(buffer);
	hb_buffer_add_utf8(buffer, std::bit_cast<const char*>(text.data()), -1, 0, -1);
	hb_buffer_guess_segment_properties(buffer);
	hb_shape(_font, buffer, nullptr, 0);
	auto glyph_count = 0u;
	auto* glyph_info = hb_buffer_get_glyph_infos(buffer, &glyph_count);
	auto* glyph_pos = hb_buffer_get_glyph_positions(buffer, &glyph_count);
	glyphs.reserve(glyph_count);
	for (auto i = 0ul; i < glyph_count; ++i) {
		glyphs.emplace_back(Glyph{
			.codepoint = glyph_info[i].codepoint,
			.offset =
				{static_cast<float>(glyph_pos[i].x_offset) / 64.0f,
				 static_cast<float>(glyph_pos[i].y_offset) / 64.0f},
			.advance =
				{static_cast<float>(glyph_pos[i].x_advance) / 64.0f,
				 static_cast<float>(glyph_pos[i].y_advance) / 64.0f},
		});
	}
	hb_buffer_destroy(buffer);
	return glyphs;
}

auto Font::get_bitmap(std::uint32_t codepoint) const -> GlyphBitmap {
	const auto result = FT_Load_Glyph(_face, codepoint, FT_LOAD_RENDER);
	assert(result == 0 && "Failed to load glyph");
	return {
		.buffer = std::vector(
			std::bit_cast<std::byte*>(_face->glyph->bitmap.buffer),
			std::bit_cast<std::byte*>(_face->glyph->bitmap.buffer) +
				(static_cast<std::uint64_t>(_face->glyph->bitmap.width * _face->glyph->bitmap.rows))
		),
		.size = {_face->glyph->bitmap.width, _face->glyph->bitmap.rows},
		.bearing = {_face->glyph->bitmap_left, _face->glyph->bitmap_top},
	};
}

} // namespace void_engine::resources
