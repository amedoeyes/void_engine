#include "void_engine/resource/shader/shader.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

namespace void_engine::resource {

Shader::Shader() : _id(glCreateProgram()) {
}

Shader::Shader(std::filesystem::path root_path) : Shader() {
	_root_path = std::move(root_path);
}

Shader::~Shader() {
	for (auto shader : _shaders) {
		glDeleteShader(shader);
	}
	glDeleteProgram(_id);
}

void Shader::bind() const {
	glUseProgram(_id);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::add_source(ShaderType type, const std::filesystem::path& path) {
	_sources[type] = _root_path / path;
}

void Shader::compile() {
	assert(!_sources.empty() && "No sources to compile");

	if (!_shaders.empty()) {
		for (auto shader : _shaders) {
			glDetachShader(_id, shader);
			glDeleteShader(shader);
		}
		_shaders.clear();
	}

	for (const auto& [type, path] : _sources) {
		const unsigned int shader = compile_source(type, path);
		glAttachShader(_id, shader);
		_shaders.push_back(shader);
	}
	glLinkProgram(_id);

	if (!_uniforms.empty()) {
		_uniforms.clear();
	}

	int uniform_count = 0;
	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &uniform_count);
	if (uniform_count != 0) {
		int max_length = 0;
		glGetProgramiv(_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
		int length = 0;
		char* name = new char[max_length];
		for (int i = 0; i < uniform_count; ++i) {
			glGetActiveUniform(_id, i, max_length, &length, nullptr, nullptr, name);
			_uniforms[name] = glGetUniformLocation(_id, name);
		}
		delete[] name;
	}
}

void Shader::set_root_path(const std::filesystem::path& root_path) {
	_root_path = root_path;
}

void Shader::set_uniform(const std::string& name, int value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniform1i(_id, it->second, value);
}

void Shader::set_uniform(const std::string& name, unsigned int value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniform1ui(_id, it->second, value);
}

void Shader::set_uniform(const std::string& name, float value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniform1f(_id, it->second, value);
}

void Shader::set_uniform(const std::string& name, const glm::vec2& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniform2fv(_id, it->second, 1, glm::value_ptr(value));
}

void Shader::set_uniform(const std::string& name, const glm::vec3& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniform3fv(_id, it->second, 1, glm::value_ptr(value));
}

void Shader::set_uniform(const std::string& name, const glm::vec4& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniform4fv(_id, it->second, 1, glm::value_ptr(value));
}

void Shader::set_uniform(const std::string& name, const glm::mat4& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	glProgramUniformMatrix4fv(_id, it->second, 1, 0u, glm::value_ptr(value));
}

auto Shader::compile_source(ShaderType type, const std::filesystem::path& path) -> unsigned int {
	std::ifstream file(path);
	assert(file.is_open() && "Failed to open file");
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

} // namespace void_engine::resource
