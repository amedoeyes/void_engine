#include "void_engine/resources/shader.hpp"

#include "void_engine/utils/logger.hpp"

#include <array>
#include <fstream>
#include <glad/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iterator>
#include <string>
#include <vector>

namespace void_engine::resources {

Shader::~Shader() {
	glDeleteProgram(_id);
}

auto Shader::bind() const -> const Shader* {
	glUseProgram(_id);
	return this;
}

void Shader::unbind() const {
	glUseProgram(0);
}

auto Shader::add(ShaderType type, const std::string& path) -> Shader* {
	_paths[type] = path;
	return this;
}

void Shader::compile() {
	if (_id != 0) {
		glDeleteProgram(_id);
		_uniforms.clear();
	}

	_id = glCreateProgram();
	std::vector<unsigned int> shaders;
	for (const auto& [type, path] : _paths) {
		const unsigned int shader = compile_source(type, path);
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

auto Shader::set_uniform(const std::string& name, int value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end()) glUniform1i(it->second, value);
	return this;
}

auto Shader::set_uniform(const std::string& name, unsigned int value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end()) glUniform1ui(it->second, value);
	return this;
}

auto Shader::set_uniform(const std::string& name, float value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end()) glUniform1f(it->second, value);
	return this;
}

auto Shader::set_uniform(const std::string& name, glm::vec2 value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end())
		glUniform2fv(it->second, 1, glm::value_ptr(value));
	return this;
}

auto Shader::set_uniform(const std::string& name, glm::vec3 value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end())
		glUniform3fv(it->second, 1, glm::value_ptr(value));
	return this;
}

auto Shader::set_uniform(const std::string& name, glm::vec4 value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end())
		glUniform4fv(it->second, 1, glm::value_ptr(value));
	return this;
}

auto Shader::set_uniform(const std::string& name, glm::mat4 value) const
	-> const Shader* {
	auto it = _uniforms.find(name);
	if (it != _uniforms.end())
		glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(value));
	return this;
}

auto Shader::compile_source(ShaderType type, const std::string& path) const
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

} // namespace void_engine::resources
