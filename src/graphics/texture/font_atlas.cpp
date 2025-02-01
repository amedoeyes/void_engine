module;

#include <cassert>
#include <glad/glad.h>

module void_engine.graphics;

import glm;
import std;
import void_engine.resources;

namespace void_engine::graphics {

FontAtlas::FontAtlas(const resources::Font& font, std::int32_t size)
	: Texture(TextureTarget::texture_2d),
		_font(font),
		_size(size) {
	set_texture_storage_2d(1, TextureInternalFormat::r8, _size);
	set_min_filter(TextureMinFilter::linear);
	set_mag_filter(TextureMagFilter::linear);
	set_wrap_s(TextureWrap::clamp_to_edge);
	set_wrap_t(TextureWrap::clamp_to_edge);
}

auto FontAtlas::glyphs(std::string_view text) -> std::vector<glyph_atlas_entry> {
	static constexpr auto padding = 1;
	auto entries = std::vector<glyph_atlas_entry>();
	const auto glyphs = _font.get().glyphs(text);
	entries.reserve(glyphs.size());
	for (const auto& glyph : glyphs) {
		auto [it, success] = _entries.try_emplace(glyph.codepoint);
		if (success) {
			const auto bitmap = _font.get().get_bitmap(glyph.codepoint);
			if (_next_glpyh_position.x + bitmap.size.x + padding > _size.x) {
				_next_glpyh_position.x = 0.0f;
				_next_glpyh_position.y += _max_glyph_height;
				_max_glyph_height = 0.0f;
			}
			if (_next_glpyh_position.y + bitmap.size.y + padding > _size.y) {
				assert(false && "Font atlas is too small");
			}
			auto prev = 0;
			glGetIntegerv(GL_UNPACK_ALIGNMENT, &prev);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			set_sub_image_2d(0, _next_glpyh_position, bitmap.size, TextureFormat::r, bitmap.buffer.data());
			glPixelStorei(GL_UNPACK_ALIGNMENT, prev);
			it->second = {
				glyph,
				bitmap,
				{
					.position = glm::vec2(_next_glpyh_position) / glm::vec2(_size),
					.size = glm::vec2(bitmap.size) / glm::vec2(_size),
				},
			};
			_next_glpyh_position.x += bitmap.size.x + padding;
			_max_glyph_height = glm::max(_max_glyph_height, bitmap.size.y + padding);
		}
		entries.emplace_back(it->second);
	}
	return entries;
}

} // namespace void_engine::graphics
