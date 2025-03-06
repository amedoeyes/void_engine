export module void_engine.graphics:font_atlas;

import :texture;
import :uv_region;

import std;
import void_engine.resources;

export namespace void_engine::graphics {

class FontAtlas final : public Texture {
public:
	using glyph_atlas_entry = std::tuple<resources::Glyph, resources::GlyphBitmap, UVRegion>;

	FontAtlas() = delete;
	explicit FontAtlas(const resources::Font& font, std::int32_t size = 1'024);

	[[nodiscard]]
	auto glyphs(std::string_view text) -> std::vector<glyph_atlas_entry>;

private:
	std::reference_wrapper<const resources::Font> _font;
	glm::ivec2 _size;
	std::unordered_map<std::uint32_t, glyph_atlas_entry> _entries;
	glm::ivec2 _next_glpyh_position{};
	std::int32_t _max_glyph_height{};
};

} // namespace void_engine::graphics
