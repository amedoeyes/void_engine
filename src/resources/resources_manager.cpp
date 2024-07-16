#include "void_engine/resources/resource_manager.hpp"
#include "void_engine/resources/shader_manager.hpp"
#include "void_engine/resources/texture_manager.hpp"
#include "void_engine/utils/get_exec_path.hpp"

#include <filesystem>

namespace void_engine::resources {

ResourceManager::ResourceManager() {
	_textures = new TextureManager();
	_shaders = new ShaderManager();
}

ResourceManager::ResourceManager(const std::filesystem::path& resources_path) {
	std::filesystem::path path =
		std::filesystem::canonical(utils::get_exec_path().parent_path() / resources_path);
	_textures = new TextureManager(path);
	_shaders = new ShaderManager(path);
}

ResourceManager::~ResourceManager() {
	delete _textures;
	delete _shaders;
}

auto ResourceManager::textures() -> TextureManager& {
	return *_textures;
}

auto ResourceManager::shaders() -> ShaderManager& {
	return *_shaders;
}

} // namespace void_engine::resources
