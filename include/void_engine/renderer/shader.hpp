#ifndef VOID_ENGINE_RENDERER_SHADER_HPP
#define VOID_ENGINE_RENDERER_SHADER_HPP

#include "common.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <unordered_map>

namespace void_engine::renderer {

class Shader {
public:
	Shader();
	~Shader();

public:
	void bind() const;
	void unbind() const;

	void add(const char* path, ShaderType type);
	void compile();
	void recompile();

	void set_uniform(const char* name, int value) const;
	void set_uniform(const char* name, unsigned int value) const;
	void set_uniform(const char* name, float value) const;
	void set_uniform(const char* name, glm::vec2 value) const;
	void set_uniform(const char* name, glm::vec3 value) const;
	void set_uniform(const char* name, glm::vec4 value) const;
	void set_uniform(const char* name, glm::mat4 value) const;

private:
	unsigned int _id;
	std::unordered_map<std::string, int> _uniforms;
	std::unordered_map<ShaderType, const char*> _paths;

private:
	auto compile_shader(const char* path, ShaderType type) const
		-> unsigned int;
};

} // namespace void_engine::renderer

#endif // !VOID_ENGINE_RENDERER_SHADER_HPP
