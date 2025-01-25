module;

#include <cassert>
#include <freetype/freetype.h>

module void_engine.resources;

import :font.manager;

import std;
import glm;

namespace void_engine::resource::font {

FontManager::FontManager(const FontManager& other) :
	_fonts(other._fonts),
	_root_path(other._root_path) {
	const int result = FT_Init_FreeType(&_ft);
	if (result != 0) {
		assert(false && "Failed to initialize FreeType");
	}
}

FontManager::FontManager(FontManager&& other) noexcept :
	_ft(other._ft),
	_fonts(std::move(other._fonts)),
	_root_path(std::move(other._root_path)) {
	other._ft = nullptr;
}

auto FontManager::operator=(const FontManager& other) -> FontManager& {
	if (this != &other) {
		_ft = other._ft;
		_fonts = other._fonts;
		_root_path = other._root_path;
	}
	return *this;
}

auto FontManager::operator=(FontManager&& other) noexcept -> FontManager& {
	if (this != &other) {
		_ft = other._ft;
		_fonts = std::move(other._fonts);
		_root_path = std::move(other._root_path);
		other._ft = nullptr;
	}
	return *this;
}

FontManager::FontManager() {
	const int result = FT_Init_FreeType(&_ft);
	if (result != 0) {
		assert(false && "Failed to initialize FreeType");
	}
}

FontManager::FontManager(std::filesystem::path root_path) : FontManager() {
	_root_path = std::move(root_path);
}

FontManager::~FontManager() {
	for (const auto& [_, font] : _fonts) {
		delete font;
	}
	FT_Done_FreeType(_ft);
}

auto FontManager::create(
	std::string_view name, const std::filesystem::path& path, unsigned int size,
	const glm::uvec2& atlas_size
) -> Font& {
	const auto [it, success] =
		_fonts.emplace(name, new Font(_ft, _root_path / path, size, atlas_size));
	assert(success && "Font already exists");
	return *it->second;
}

auto FontManager::create(
	std::string_view name, std::span<const std::byte> data, unsigned int size,
	const glm::uvec2& atlas_size
) -> Font& {
	const auto [it, success] = _fonts.emplace(name, new Font(_ft, data, size, atlas_size));
	assert(success && "Font already exists");
	return *it->second;
}

void FontManager::destroy(std::string_view name) {
	const auto it = _fonts.find(name.data());
	assert(it != _fonts.end() && "Font does not exist");
	delete it->second;
	_fonts.erase(it);
}

auto FontManager::get(std::string_view name) -> Font& {
	const auto it = _fonts.find(name.data());
	assert(it != _fonts.end() && "Font does not exist");
	return *it->second;
}

} // namespace void_engine::resource::font
