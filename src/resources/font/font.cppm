export module void_engine.resources:font;

import :font.glyph;
import :texture;
import :texture.enums;

import glm;
import std;

using FT_Library = struct FT_LibraryRec_*;
using FT_Face = struct FT_FaceRec_*;
struct hb_font_t;

export namespace void_engine::resource::font {

class Font {
public:
	Font(const Font&) = delete;
	Font(Font&&) = delete;
	auto operator=(const Font&) = delete;
	auto operator=(Font&& other) = delete;
	Font(
		FT_Library ft, const std::filesystem::path& path, unsigned int size = 48,
		glm::uvec2 atlas_size = {1024, 1024}
	);
	Font(
		FT_Library ft, std::span<const std::byte> data, unsigned int size = 48,
		glm::uvec2 atlas_size = {1024, 1024}
	);
	~Font();

	void add_fallback(const std::filesystem::path& path);
	void add_fallback(std::span<const std::byte> data);

	[[nodiscard]] auto get_glyphs(std::u32string_view text) const -> std::vector<Glyph>;
	[[nodiscard]] auto get_texture() const -> const texture::Texture&;
	[[nodiscard]] auto get_line_height() const -> unsigned int;
	[[nodiscard]] auto get_fonts() const -> const std::vector<hb_font_t*>&;

private:
	FT_Library _ft = nullptr;
	std::vector<FT_Face> _faces;
	std::vector<hb_font_t*> _fonts;
	unsigned int _size;
	glm::uvec2 _atlas_size;
	texture::Texture _texture = texture::Texture(resource::Target::texture_2d);
	mutable std::unordered_map<unsigned long, Glyph> _glyphs;
	mutable glm::uvec2 _next_glpyh_position = glm::vec2(0.0f);
	mutable unsigned int _max_glyph_height = 0.0f;

	[[nodiscard]] auto load_font(const std::filesystem::path& path, unsigned int size) -> FT_Face;
	[[nodiscard]] auto load_font(std::span<const std::byte> data, unsigned int size) -> FT_Face;
	[[nodiscard]] auto get_glyph(unsigned int index, unsigned int codepoint) const -> const Glyph&;
	[[nodiscard]] auto get_glyphs(unsigned int index, std::u32string_view text) const
		-> std::vector<Glyph>;
};

} // namespace void_engine::resource::font
