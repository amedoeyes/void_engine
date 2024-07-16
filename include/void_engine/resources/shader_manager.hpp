#ifndef VOID_ENGINE_RESOURCES_SHADER_MANAGER_HPP
#define VOID_ENGINE_RESOURCES_SHADER_MANAGER_HPP

#include "void_engine/resources/shader.hpp"

#include <string>
#include <unordered_map>

namespace void_engine::resources {

class ShaderManager {
public:
	ShaderManager(const ShaderManager&) = default;
	ShaderManager(ShaderManager&&) = delete;
	auto operator=(const ShaderManager&) -> ShaderManager& = default;
	auto operator=(ShaderManager&&) -> ShaderManager& = delete;
	ShaderManager() = default;
	~ShaderManager();

	auto create(std::string_view name) -> Shader&;
	void destroy(std::string_view name);
	auto get(std::string_view name) -> Shader&;

private:
	std::unordered_map<std::string, Shader*> _shaders;
};

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_SHADER_MANAGER_HPP
