export module void_engine.graphics:shader;

import :shader_enums;
import :shader_source;

import std;
import glm;

export namespace void_engine::graphics {

class Shader {
public:
	Shader(const Shader& other);
	Shader(Shader&& other) noexcept;
	auto operator=(const Shader& other) -> Shader&;
	auto operator=(Shader&& other) noexcept -> Shader&;
	Shader();
	Shader(std::initializer_list<ShaderSource> sources);
	~Shader();

	void bind() const;
	static void unbind();

	void add_source(ShaderType type, const std::filesystem::path& path, ShaderFormat format = ShaderFormat::glsl);
	void add_source(ShaderType type, std::span<const std::byte> source, ShaderFormat format = ShaderFormat::glsl);
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
	std::vector<ShaderSource> _sources;
	std::vector<unsigned int> _shaders;
	std::unordered_map<std::string, int> _uniforms;

	static auto compile_source(const ShaderSource& source) -> unsigned int;
	static auto compile_source_glsl(const ShaderSource& source) -> unsigned int;
	static auto compile_source_spirv(const ShaderSource& source) -> unsigned int;
};

} // namespace void_engine::graphics
