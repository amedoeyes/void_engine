#include "void_engine/resource/texture/texture_manager.hpp"

#include "void_engine/resource/texture/texture.hpp"
#include "void_engine/utility/image.hpp"

#include <cassert>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace void_engine::resource {

TextureManager::TextureManager(std::filesystem::path root_path) : _root_path(std::move(root_path)) {
}

TextureManager::~TextureManager() {
	for (const auto& [_, texture] : _textures) {
		delete texture;
	}
}

auto TextureManager::create_2d(std::string_view name, const std::filesystem::path& path)
	-> Texture& {
	assert(_textures.find(name.data()) == _textures.end() && "Texture already exists");

	const utility::Image image = utility::read_image(_root_path / path, true);

	auto* texture = new Texture(TextureTarget::texture_2d);
	texture->set_texture_storage_2d(1, TextureInternalFormat::rgba8, image.size);

	TextureFormat format = TextureFormat::none;
	switch (image.color_type) {
		using enum utility::ImageColorType;
		case gray: format = TextureFormat::red; break;
		case gray_alpha: format = TextureFormat::rg; break;
		case rgb: format = TextureFormat::rgb; break;
		case rgba: format = TextureFormat::rgba; break;
		default: std::unreachable();
	}

	texture->set_sub_image_2d(0, {0, 0}, image.size, format, image.data.data());

	const auto [it, _] = _textures.emplace(name.data(), texture);
	return *(it->second);
}

void TextureManager::destroy(std::string_view name) {
	const auto it = _textures.find(name.data());
	assert(it != _textures.end() && "Texture does not exist");
	delete it->second;
	_textures.erase(it);
}

auto TextureManager::get(std::string_view name) -> Texture& {
	auto it = _textures.find(name.data());
	assert(it != _textures.end() && "Texture does not exist");
	return *(it->second);
}

void TextureManager::set_root_path(const std::filesystem::path& root_path) {
	_root_path = root_path;
}

} // namespace void_engine::resource
