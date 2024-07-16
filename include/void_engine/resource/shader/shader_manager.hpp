#ifndef VOID_ENGINE_RESOURCE_SHADER_SHADER_MANAGER_HPP
#define VOID_ENGINE_RESOURCE_SHADER_SHADER_MANAGER_HPP

#include "void_engine/resource/shader/shader.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace void_engine::resource {

class ShaderManager {
public:
	ShaderManager(const ShaderManager&) = default;
	ShaderManager(ShaderManager&&) = delete;
	auto operator=(const ShaderManager&) -> ShaderManager& = default;
	auto operator=(ShaderManager&&) -> ShaderManager& = delete;
	ShaderManager() = default;
	explicit ShaderManager(std::filesystem::path root_path);
	~ShaderManager();

	auto create(std::string_view name) -> Shader&;
	void destroy(std::string_view name);
	auto get(std::string_view name) -> Shader&;

	void set_root_path(const std::filesystem::path& root_path);

private:
	std::unordered_map<std::string, Shader*> _shaders;
	std::filesystem::path _root_path;
};

} // namespace void_engine::resource

#endif // !VOID_ENGINE_RESOURCE_SHADER_SHADER_MANAGER_HPP
