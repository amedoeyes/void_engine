#include "void_engine/resource/font/font_manager.hpp"
#include "void_engine/resource/resource_manager.hpp"
#include "void_engine/resource/shader/shader_manager.hpp"
#include "void_engine/resource/texture/texture_manager.hpp"
#include "void_engine/utility/get_exec_path.hpp"

#include <filesystem>

namespace void_engine::resource {

ResourceManager::ResourceManager() {
	_textures = new texture::TextureManager();
	_shaders = new shader::ShaderManager();
	_fonts = new font::FontManager();
}

ResourceManager::ResourceManager(const std::filesystem::path& resources_path) {
	const std::filesystem::path path =
		std::filesystem::canonical(utility::get_exec_path().parent_path() / resources_path);
	_textures = new texture::TextureManager(path);
	_shaders = new shader::ShaderManager(path);
	_fonts = new font::FontManager(path);
}

ResourceManager::~ResourceManager() {
	delete _textures;
	delete _shaders;
	delete _fonts;
}

auto ResourceManager::textures() -> texture::TextureManager& {
	return *_textures;
}

auto ResourceManager::shaders() -> shader::ShaderManager& {
	return *_shaders;
}

auto ResourceManager::fonts() -> font::FontManager& {
	return *_fonts;
}

} // namespace void_engine::resource
