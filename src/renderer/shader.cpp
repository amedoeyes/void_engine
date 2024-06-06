#include "void_engine/renderer/shader.hpp"

#include "void_engine/renderer/common.hpp"
#include "void_engine/utils/logger.hpp"

#include <array>
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iterator>
#include <string>
#include <vector>

namespace void_engine::renderer {

Shader::Shader() : _id(glCreateProgram()) {
}
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
		const unsigned int shader = compile_shader(path, type);
		glAttachShader(_id, shader);
		shaders.push_back(shader);
	}
	glLinkProgram(_id);

	for (auto shader : shaders) {
		glDeleteShader(shader);
	}

	int uniform_count;
	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &uniform_count);
	for (int i = 0; i < uniform_count; i++) {
		std::array<char, 128> name;
		glGetActiveUniform(
			_id, i, name.size(), nullptr, nullptr, nullptr, name.data()
		);
		const int location = glGetUniformLocation(_id, name.data());
		if (location == -1) continue;
		_uniforms[name.data()] = location;
	}
}

void Shader::recompile() {
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

auto Shader::compile_shader(const char* path, ShaderType type) const
	-> unsigned int {
	std::ifstream file(path);
	if (!file.is_open()) {
		utils::Logger::error("Failed to open shader file: {}", path);
		return 0;
	}
	const std::string source(
		(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()
	);
	file.close();

	const unsigned int shader = glCreateShader(static_cast<unsigned int>(type));
	const char* source_c = source.c_str();
	glShaderSource(shader, 1, &source_c, nullptr);
	glCompileShader(shader);

	return shader;
}

} // namespace void_engine::renderer
