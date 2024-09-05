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

	void add_source(ShaderType type, const std::filesystem::path& path);
	void add_source(ShaderType type, std::string_view source);
	void add_source(ShaderType type, const std::string& source);
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
	std::unordered_map<ShaderType, std::variant<std::filesystem::path, std::string>> _sources;
	std::vector<unsigned int> _shaders;
	std::unordered_map<std::string, int> _uniforms;

	static auto compile_source(ShaderType type, const std::filesystem::path& path) -> unsigned int;
	static auto compile_source(ShaderType type, const std::string& source) -> unsigned int;
};

} // namespace void_engine::resource

#endif // !VOID_ENGINE_RESOURCE_SHADER_SHADER_HPP
