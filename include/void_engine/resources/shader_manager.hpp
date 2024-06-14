#ifndef VOID_ENGINE_RESOURCES_SHADER_MANAGER_HPP
#define VOID_ENGINE_RESOURCES_SHADER_MANAGER_HPP

#include "shader.hpp"

#include <string>
#include <unordered_map>

namespace void_engine::resources {

class ShaderManager {
public:
	static void terminate();

public:
	static auto create(const std::string& name) -> Shader*;
	static void destroy(const std::string& name);
	static auto get(const std::string& name) -> Shader*;

private:
	static std::unordered_map<std::string, Shader*> _shaders;
};

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_SHADER_MANAGER_HPP
