#ifndef VOID_ENGINE_RENDERER_SHADER_HPP
#define VOID_ENGINE_RENDERER_SHADER_HPP

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

#include "common.hpp"

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
	void recomplie();

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
	unsigned int compile_shader(const char* path, ShaderType type) const;
};

}  // namespace void_engine::renderer

#endif	// !VOID_ENGINE_RENDERER_SHADER_HPP
