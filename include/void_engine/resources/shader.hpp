#ifndef VOID_ENGINE_RESOURCES_SHADER_HPP
#define VOID_ENGINE_RESOURCES_SHADER_HPP

#include <glad/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <unordered_map>

namespace void_engine::resources {

enum class ShaderType {
	compute = GL_COMPUTE_SHADER,
	vertex = GL_VERTEX_SHADER,
	tess_control = GL_TESS_CONTROL_SHADER,
	tess_evaluation = GL_TESS_EVALUATION_SHADER,
	geometry = GL_GEOMETRY_SHADER,
	fragment = GL_FRAGMENT_SHADER
};

class Shader {
public:
	~Shader();

public:
	auto bind() const -> const Shader*;
	void unbind() const;

	auto add(ShaderType type, const std::string& path) -> Shader*;
	void compile();

	auto set_uniform(const std::string& name, int value) const -> const Shader*;
	auto set_uniform(const std::string& name, unsigned int value) const
		-> const Shader*;
	auto set_uniform(const std::string& name, float value) const
		-> const Shader*;
	auto set_uniform(const std::string& name, glm::vec2 value) const
		-> const Shader*;
	auto set_uniform(const std::string& name, glm::vec3 value) const
		-> const Shader*;
	auto set_uniform(const std::string& name, glm::vec4 value) const
		-> const Shader*;
	auto set_uniform(const std::string& name, glm::mat4 value) const
		-> const Shader*;

private:
	unsigned int _id = 0;
	std::unordered_map<std::string, int> _uniforms;
	std::unordered_map<ShaderType, std::string> _paths;

private:
	auto compile_source(ShaderType type, const std::string& path) const
		-> unsigned int;
};

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_SHADER_HPP
