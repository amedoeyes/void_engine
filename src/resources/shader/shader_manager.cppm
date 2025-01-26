export module void_engine.resources:shader.manager;

import :shader;

import std;

export namespace void_engine::resource::shader {

class ShaderManager {
public:
	ShaderManager(const ShaderManager&) = default;
	ShaderManager(ShaderManager&&) = delete;
	auto operator=(const ShaderManager&) -> ShaderManager& = default;
	auto operator=(ShaderManager&&) -> ShaderManager& = delete;
	ShaderManager() = default;
	explicit ShaderManager(std::filesystem::path root_path);
	~ShaderManager();

	auto create(std::string_view name) -> Shader&;
	void destroy(std::string_view name);
	auto get(std::string_view name) -> Shader&;

	void set_root_path(const std::filesystem::path& root_path);

private:
	std::unordered_map<std::string, Shader*> _shaders;
	std::filesystem::path _root_path;
};

} // namespace void_engine::resource::shader
