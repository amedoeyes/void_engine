#ifndef VOID_ENGINE_RESOURCES_TEXTURE_MANAGER_HPP
#define VOID_ENGINE_RESOURCES_TEXTURE_MANAGER_HPP

#include "texture.hpp"

#include <string>
#include <unordered_map>

namespace void_engine::resources {

class TextureManager {
public:
	static auto create_2d(const std::string& name, const std::string& path)
		-> Texture*;
	static void destroy(const std::string& name);
	static auto get(const std::string& name) -> Texture*;
	static void terminate();

private:
	static std::unordered_map<std::string, Texture*> _textures;
};

} // namespace void_engine::resources

#endif // !#ifndef VOID_ENGINE_RESOURCES_TEXTURE_MANAGER_HPP
