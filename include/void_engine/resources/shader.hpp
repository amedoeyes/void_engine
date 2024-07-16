#ifndef VOID_ENGINE_RESOURCES_SHADER_HPP
#define VOID_ENGINE_RESOURCES_SHADER_HPP

#include <filesystem>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace void_engine::resources {

enum class ShaderType {
	compute = 0x91B9,
	vertex = 0x8B31,
	tess_control = 0x8E88,
	tess_evaluation = 0x8E87,
	geometry = 0x8DD9,
	fragment = 0x8B30
};

class Shader {
public:
	Shader(const Shader&) = default;
	Shader(Shader&&) = delete;
	auto operator=(const Shader&) -> Shader& = default;
	auto operator=(Shader&&) -> Shader& = delete;
	Shader();
	explicit Shader(std::filesystem::path root_path);
	~Shader();

	void bind() const;
	static void unbind();

	void add_source(ShaderType type, const std::filesystem::path& path);
	void compile();

	void set_root_path(const std::filesystem::path& root_path);

	void set_uniform(const std::string& name, int value) const;
	void set_uniform(const std::string& name, unsigned int value) const;
	void set_uniform(const std::string& name, float value) const;
	void set_uniform(const std::string& name, const glm::vec2& value) const;
	void set_uniform(const std::string& name, const glm::vec3& value) const;
	void set_uniform(const std::string& name, const glm::vec4& value) const;
	void set_uniform(const std::string& name, const glm::mat4& value) const;

private:
	unsigned int _id = 0;
	std::filesystem::path _root_path;
	std::unordered_map<ShaderType, std::string> _sources;
	std::vector<unsigned int> _shaders;
	std::unordered_map<std::string, int> _uniforms;

	static auto compile_source(ShaderType type, const std::filesystem::path& path) -> unsigned int;
};

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_SHADER_HPP
