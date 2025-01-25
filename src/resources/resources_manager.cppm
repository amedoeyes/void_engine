export module void_engine.resources:resources_manager;

import :font.manager;
import :shader.manager;
import :texture.manager;

import std;

export namespace void_engine::resource {

class ResourceManager {
public:
	ResourceManager(const ResourceManager&) = default;
	ResourceManager(ResourceManager&&) = delete;
	auto operator=(const ResourceManager&) -> ResourceManager& = default;
	auto operator=(ResourceManager&&) -> ResourceManager& = delete;
	ResourceManager();
	explicit ResourceManager(const std::filesystem::path& resources_path);
	~ResourceManager();

	auto textures() -> texture::TextureManager&;
	auto shaders() -> shader::ShaderManager&;
	auto fonts() -> font::FontManager&;

private:
	texture::TextureManager* _textures;
	shader::ShaderManager* _shaders;
	font::FontManager* _fonts;
};

} // namespace void_engine::resource
