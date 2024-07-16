#include "void_engine/resource/texture/texture_manager.hpp"

#include "void_engine/resource/image.hpp"
#include "void_engine/resource/texture/texture.hpp"

#include <cassert>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>
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

	const Image* image = read_image(_root_path / path, true);
	assert(image != nullptr && "Failed to read image");

	const glm::vec2 image_size = {image->width, image->height};

	auto* texture = new Texture(TextureTarget::texture_2d);
	texture->set_texture_storage_2d(1, TextureInternalFormat::rgba8, image_size);

	TextureFormat format = TextureFormat::none;
	switch (image->color_type) {
		case ImageColorType::gray: format = TextureFormat::red; break;
		case ImageColorType::gray_alpha: format = TextureFormat::rg; break;
		case ImageColorType::rgb: format = TextureFormat::rgb; break;
		case ImageColorType::rgba: format = TextureFormat::rgba; break;
		case ImageColorType::palette: format = TextureFormat::rgb; break;
		default: assert(false && "Invalid color type");
	}

	texture->set_sub_image_2d(0, {0, 0}, image_size, format, image->bytes.data());
	delete image;

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
