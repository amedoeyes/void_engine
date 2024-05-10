#include "void_engine/renderer/shader.hpp"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <string_view>
#include <vector>

#include "void_engine/logger.hpp"

namespace void_engine::renderer {

Shader::Shader() : _id(glCreateProgram()) {}
Shader::~Shader() {
	glDeleteProgram(_id);
}

void Shader::bind() const {
	glUseProgram(_id);
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::add(const char* path, ShaderType type) {
	_paths[type] = path;
}

void Shader::compile() {
	std::vector<unsigned int> shaders;
	for (const auto& [type, path] : _paths) {
		unsigned int shader = compile_shader(path, type);
		glAttachShader(_id, shader);
		shaders.push_back(shader);
	}
	glLinkProgram(_id);

	for (const auto shader : shaders) {
		glDeleteShader(shader);
	}

	int uniform_count;
	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &uniform_count);
	for (int i = 0; i < uniform_count; i++) {
		char name[128];
		glGetActiveUniform(_id, i, 128, nullptr, nullptr, nullptr, name);
		int location = glGetUniformLocation(_id, name);
		if (location == -1) continue;
		_uniforms[name] = location;
	}
}

void Shader::recomplie() {
	glDeleteProgram(_id);
	_uniforms.clear();
	_id = glCreateProgram();
	compile();
}

void Shader::set_uniform(const char* name, int value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniform1i(it->second, value);
}

void Shader::set_uniform(const char* name, unsigned int value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniform1ui(it->second, value);
}

void Shader::set_uniform(const char* name, float value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniform1f(it->second, value);
}

void Shader::set_uniform(const char* name, glm::vec2 value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniform2fv(it->second, 1, glm::value_ptr(value));
}

void Shader::set_uniform(const char* name, glm::vec3 value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniform3fv(it->second, 1, glm::value_ptr(value));
}

void Shader::set_uniform(const char* name, glm::vec4 value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniform4fv(it->second, 1, glm::value_ptr(value));
}

void Shader::set_uniform(const char* name, glm::mat4 value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) return;
	glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::compile_shader(const char* path, ShaderType type) const {
	std::ifstream file(path);
	if (!file.is_open()) {
		Logger::error("Failed to open shader file: {}", path);
		return 0;
	}
	std::string source(
		(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()
	);
	file.close();

	unsigned int shader = glCreateShader(static_cast<unsigned int>(type));
	const char* source_c = source.c_str();
	glShaderSource(shader, 1, &source_c, nullptr);
	glCompileShader(shader);

	return shader;
}

}  // namespace void_engine::renderer
