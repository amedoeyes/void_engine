#ifndef VOID_ENGINE_RESOURCE_RESOURCE_MANAGER_HPP
#define VOID_ENGINE_RESOURCE_RESOURCE_MANAGER_HPP

#include "void_engine/resource/font/font_manager.hpp"
#include "void_engine/resource/shader/shader_manager.hpp"
#include "void_engine/resource/texture/texture_manager.hpp"

#include <filesystem>

namespace void_engine::resource {

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
	auto shaders() -> shader::ShaderManager&;
	auto fonts() -> font::FontManager&;

private:
	TextureManager* _textures;
	shader::ShaderManager* _shaders;
	font::FontManager* _fonts;
};

} // namespace void_engine::resource

#endif // !VOID_ENGINE_RESOURCE_RESOURCE_MANAGER_HPP
