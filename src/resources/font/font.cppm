module;

#include <freetype/freetype.h>
#include <hb.h>

export module void_engine.resources:font;

import :glyph;
import :glyph_bitmap;

import glm;
import std;

export namespace void_engine::resources {

class Font {
public:
	Font(const Font&) = delete;
	Font(Font&&) = delete;
	auto operator=(const Font&) = delete;
	auto operator=(Font&& other) = delete;
	Font() = delete;
	explicit Font(const std::filesystem::path& path, std::int32_t size = 48);
	explicit Font(std::span<const std::byte> data, std::int32_t size = 48);
	~Font();

	[[nodiscard]]
	auto glyphs(std::string_view text) const -> std::vector<Glyph>;
	[[nodiscard]]
	auto get_bitmap(std::uint32_t codepoint) const -> GlyphBitmap;
	[[nodiscard]]
	auto get_line_height() const -> float;

private:
	static inline FT_Library _ft = nullptr;
	static inline std::int32_t _instance_count = 0;
	FT_Face _face = nullptr;
	hb_font_t* _font = nullptr;
	std::int32_t _size;
};

} // namespace void_engine::resources
