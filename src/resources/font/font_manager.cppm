export module void_engine.resources:font.manager;

import :font;

import std;
import glm;

using FT_Library = struct FT_LibraryRec_*;

export namespace void_engine::resource::font {

class FontManager {
public:
	FontManager(const FontManager& other);
	FontManager(FontManager&& other) noexcept;
	auto operator=(const FontManager& other) -> FontManager&;
	auto operator=(FontManager&& other) noexcept -> FontManager&;
	FontManager();
	explicit FontManager(std::filesystem::path root_path);
	~FontManager();

	auto create(
		std::string_view name, const std::filesystem::path& path, unsigned int size = 48,
		const glm::uvec2& atlas_size = {1024, 1024}
	) -> Font&;
	auto create(
		std::string_view name, std::span<const std::byte> data, unsigned int size = 48,
		const glm::uvec2& atlas_size = {1024, 1024}
	) -> Font&;
	void destroy(std::string_view name);
	auto get(std::string_view name) -> Font&;

private:
	FT_Library _ft = nullptr;
	std::unordered_map<std::string, Font*> _fonts;
	std::filesystem::path _root_path;
};

} // namespace void_engine::resource::font
