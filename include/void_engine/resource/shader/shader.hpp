#ifndef VOID_ENGINE_RESOURCE_SHADER_SHADER_HPP
#define VOID_ENGINE_RESOURCE_SHADER_SHADER_HPP

#include <cstdint>
#include <filesystem>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

namespace void_engine::resource {

enum class ShaderType : std::uint16_t {
	compute = 0x91B9,
	vertex = 0x8B31,
	tess_control = 0x8E88,
	tess_evaluation = 0x8E87,
	geometry = 0x8DD9,
	fragment = 0x8B30
};

enum class ShaderFormat : std::uint8_t {
	glsl,
	spirv,
};

struct ShaderSource {
	ShaderType type;
	ShaderFormat format;
	std::variant<std::filesystem::path, std::string> data;
};

class Shader {
public:
	Shader(const Shader& other);
	Shader(Shader&& other) noexcept;
	auto operator=(const Shader& other) -> Shader&;
	auto operator=(Shader&& other) noexcept -> Shader&;
	Shader();
	explicit Shader(std::filesystem::path root_path);
	~Shader();

	void bind() const;
	static void unbind();

	void add_source_path(
		ShaderType type, const std::filesystem::path& path, ShaderFormat format = ShaderFormat::glsl
	);
	void add_source(
		ShaderType type, std::string_view source, ShaderFormat format = ShaderFormat::glsl
	);
	void add_source(
		ShaderType type, std::span<const unsigned char> source, ShaderFormat format = ShaderFormat::glsl
	);
	void compile();

	void set_uniform(unsigned int index, int value) const;
	void set_uniform(unsigned int index, unsigned int value) const;
	void set_uniform(unsigned int index, float value) const;
	void set_uniform(unsigned int index, const glm::vec2& value) const;
	void set_uniform(unsigned int index, const glm::vec3& value) const;
	void set_uniform(unsigned int index, const glm::vec4& value) const;
	void set_uniform(unsigned int index, const glm::mat4& value) const;
	void set_uniform(const std::string& name, int value) const;
	void set_uniform(const std::string& name, unsigned int value) const;
	void set_uniform(const std::string& name, float value) const;
	void set_uniform(const std::string& name, const glm::vec2& value) const;
	void set_uniform(const std::string& name, const glm::vec3& value) const;
	void set_uniform(const std::string& name, const glm::vec4& value) const;
	void set_uniform(const std::string& name, const glm::mat4& value) const;
	void set_root_path(const std::filesystem::path& root_path);

private:
	unsigned int _id = 0;
	std::filesystem::path _root_path;
	std::vector<ShaderSource> _sources;
	std::vector<unsigned int> _shaders;
	std::unordered_map<std::string, int> _uniforms;

	static auto compile_source(const ShaderSource& source) -> unsigned int;
	static auto compile_source_glsl(const ShaderSource& source) -> unsigned int;
	static auto compile_source_spirv(const ShaderSource& source) -> unsigned int;
};

} // namespace void_engine::resource

#endif // !VOID_ENGINE_RESOURCE_SHADER_SHADER_HPP
