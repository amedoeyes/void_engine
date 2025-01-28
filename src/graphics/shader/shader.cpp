module;

#include <cassert>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

module void_engine.graphics;

import std;
import glm;

namespace void_engine::graphics {

Shader::Shader(const Shader& other) : _id(glCreateProgram()), _sources(other._sources) {
	compile();
}

Shader::Shader(Shader&& other) noexcept :
	_id(other._id),
	_sources(std::move(other._sources)),
	_shaders(std::move(other._shaders)),
	_uniforms(std::move(other._uniforms)) {
	other._id = 0;
}

auto Shader::operator=(const Shader& other) -> Shader& {
	if (this == &other) {
		return *this;
	}
	_sources = other._sources;
	compile();
	return *this;
}

auto Shader::operator=(Shader&& other) noexcept -> Shader& {
	_id = other._id;
	_sources = std::move(other._sources);
	_shaders = std::move(other._shaders);
	_uniforms = std::move(other._uniforms);
	other._id = 0;
	return *this;
}

Shader::Shader() : _id(glCreateProgram()) {
}

Shader::Shader(std::initializer_list<ShaderSource> sources) : Shader() {
	std::ranges::move(sources, std::back_inserter(_sources));
	compile();
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

void Shader::add_source(ShaderType type, const std::filesystem::path& path, ShaderFormat format) {
	_sources.push_back({type, format, path});
}

void Shader::add_source(ShaderType type, std::span<const std::byte> source, ShaderFormat format) {
	_sources.push_back({type, format, source});
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

	for (const auto& source : _sources) {
		const unsigned int shader = compile_source(source);
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

void Shader::set_uniform(unsigned int index, int value) const {
	glProgramUniform1i(_id, static_cast<GLint>(index), value);
}

void Shader::set_uniform(unsigned int index, unsigned int value) const {
	glProgramUniform1ui(_id, static_cast<GLint>(index), value);
}

void Shader::set_uniform(unsigned int index, float value) const {
	glProgramUniform1f(_id, static_cast<GLint>(index), value);
}

void Shader::set_uniform(unsigned int index, const glm::vec2& value) const {
	glProgramUniform2fv(_id, static_cast<GLint>(index), 1, glm::value_ptr(value));
}

void Shader::set_uniform(unsigned int index, const glm::vec3& value) const {
	glProgramUniform3fv(_id, static_cast<GLint>(index), 1, glm::value_ptr(value));
}

void Shader::set_uniform(unsigned int index, const glm::vec4& value) const {
	glProgramUniform4fv(_id, static_cast<GLint>(index), 1, glm::value_ptr(value));
}

void Shader::set_uniform(unsigned int index, const glm::mat4& value) const {
	glProgramUniformMatrix4fv(_id, static_cast<GLint>(index), 1, 0u, glm::value_ptr(value));
}

void Shader::set_uniform(const std::string& name, int value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

void Shader::set_uniform(const std::string& name, unsigned int value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

void Shader::set_uniform(const std::string& name, float value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

void Shader::set_uniform(const std::string& name, const glm::vec2& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

void Shader::set_uniform(const std::string& name, const glm::vec3& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

void Shader::set_uniform(const std::string& name, const glm::vec4& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

void Shader::set_uniform(const std::string& name, const glm::mat4& value) const {
	auto it = _uniforms.find(name);
	if (it == _uniforms.end()) {
		return;
	}
	set_uniform(it->second, value);
}

auto Shader::compile_source_glsl(const ShaderSource& source) -> unsigned int {
	std::string buffer;
	if (std::holds_alternative<std::filesystem::path>(source.data)) {
		const auto& file_path = std::get<std::filesystem::path>(source.data);
		std::ifstream file(file_path, std::ios::binary | std::ios::ate);
		assert(file.is_open() && "Failed to open file");
		std::streamsize file_size = file.tellg();
		file.seekg(0, std::ios::beg);
		buffer.resize(file_size);
		file.read(buffer.data(), file_size);
	} else {
		const auto& bytes = std::get<std::span<const std::byte>>(source.data);
		buffer.assign(std::bit_cast<const char*>(bytes.data()), bytes.size());
	}
	const char* source_code_c = buffer.c_str();
	const unsigned int shader = glCreateShader(static_cast<GLenum>(source.type));
	glShaderSource(shader, 1, &source_code_c, nullptr);
	glCompileShader(shader);
	return shader;
}

auto Shader::compile_source_spirv(const ShaderSource& source) -> unsigned int {
	std::string buffer;
	if (std::holds_alternative<std::filesystem::path>(source.data)) {
		const auto& file_path = std::get<std::filesystem::path>(source.data);
		std::ifstream file(file_path, std::ios::binary | std::ios::ate);
		assert(file.is_open() && "Failed to open file");
		std::streamsize file_size = file.tellg();
		file.seekg(0, std::ios::beg);
		buffer.resize(file_size);
		file.read(buffer.data(), file_size);
	} else {
		const auto& bytes = std::get<std::span<const std::byte>>(source.data);
		buffer.assign(std::bit_cast<const char*>(bytes.data()), bytes.size());
	}
	const unsigned int shader = glCreateShader(static_cast<GLenum>(source.type));
	glShaderBinary(
		1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), static_cast<GLsizei>(buffer.size())
	);
	glSpecializeShader(shader, "main", 0, nullptr, nullptr);
	return shader;
}

auto Shader::compile_source(const ShaderSource& source) -> unsigned int {
	switch (source.format) {
		case ShaderFormat::glsl: return compile_source_glsl(source);
		case ShaderFormat::spirv: return compile_source_spirv(source);
		default: std::unreachable();
	}
}

} // namespace void_engine::graphics
