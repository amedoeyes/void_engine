#ifndef VOID_ENGINE_RESOURCES_TEXTURE_MANAGER_HPP
#define VOID_ENGINE_RESOURCES_TEXTURE_MANAGER_HPP

#include "void_engine/resources/texture.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace void_engine::resources {

class TextureManager {
public:
	TextureManager(const TextureManager&) = default;
	TextureManager(TextureManager&&) = delete;
	auto operator=(const TextureManager&) -> TextureManager& = default;
	auto operator=(TextureManager&&) -> TextureManager& = delete;
	TextureManager() = default;
	explicit TextureManager(std::filesystem::path root_path);
	~TextureManager();

	auto create_2d(std::string_view name, const std::filesystem::path& path) -> Texture&;
	void destroy(std::string_view name);
	auto get(std::string_view name) -> Texture&;

	void set_root_path(const std::filesystem::path& root_path);

private:
	std::unordered_map<std::string, Texture*> _textures;
	std::filesystem::path _root_path;
};

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_TEXTURE_MANAGER_HPP
