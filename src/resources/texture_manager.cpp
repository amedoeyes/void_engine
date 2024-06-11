#include "void_engine/resources/texture_manager.hpp"

#include "void_engine/resources/image.hpp"
#include "void_engine/resources/texture.hpp"

#include <stdexcept>

namespace void_engine::resources {

std::unordered_map<std::string, Texture*> TextureManager::_textures;

auto TextureManager::create_2d(const std::string& name, const std::string& path)
	-> Texture* {

	const auto it = _textures.find(name);
	if (it != _textures.end()) delete it->second;

	const Image* image = read_image(path, true);
	if (image == nullptr)
		throw std::runtime_error("Failed to load image: " + path);

	auto* texture = new Texture(TextureTarget::texture_2d);
	texture->set_size({image->width, image->height});

	int format;
	switch (image->color_type) {
		case ImageColorType::gray: format = GL_RED; break;
		case ImageColorType::gray_alpha: format = GL_RG; break;
		case ImageColorType::rgb: format = GL_RGB; break;
		case ImageColorType::rgba: format = GL_RGBA; break;
		case ImageColorType::palette: format = GL_RGB; break;
	}

	texture->bind();
	glTexImage2D(
		GL_TEXTURE_2D, 0, format, static_cast<int>(image->width),
		static_cast<int>(image->height), 0, format, GL_UNSIGNED_BYTE,
		image->bytes.data()
	);

	_textures[name] = texture;
	delete image;
	return texture;
}

void TextureManager::destroy(const std::string& name) {
	const auto it = _textures.find(name);
	if (it == _textures.end())
		throw std::runtime_error("Texture not found: " + name);
	delete it->second;
	_textures.erase(it);
}

auto TextureManager::get(const std::string& name) -> Texture* {
	const auto it = _textures.find(name);
	if (it == _textures.end())
		throw std::runtime_error("Texture not found: " + name);
	return it->second;
}

void TextureManager::terminate() {
	for (const auto& [_, texture] : _textures) delete texture;
	_textures.clear();
}

} // namespace void_engine::resources
