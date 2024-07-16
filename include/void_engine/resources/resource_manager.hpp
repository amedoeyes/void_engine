#ifndef VOID_ENGINE_RESOURCES_RESOURCE_MANAGER_HPP
#define VOID_ENGINE_RESOURCES_RESOURCE_MANAGER_HPP

#include "void_engine/resources/shader_manager.hpp"
#include "void_engine/resources/texture_manager.hpp"

namespace void_engine::resources {

class ResourceManager {
public:
	ResourceManager(const ResourceManager&) = default;
	ResourceManager(ResourceManager&&) = delete;
	auto operator=(const ResourceManager&) -> ResourceManager& = default;
	auto operator=(ResourceManager&&) -> ResourceManager& = delete;
	ResourceManager();
	explicit ResourceManager(const std::filesystem::path& resources_path);
	~ResourceManager();

	auto textures() -> TextureManager&;
	auto shaders() -> ShaderManager&;

private:
	TextureManager* _textures;
	ShaderManager* _shaders;
};

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_RESOURCE_MANAGER_HPP
