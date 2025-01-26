export module void_engine.resources:shader.source;

import :shader.enums;

import std;

export namespace void_engine::resource::shader {

struct ShaderSource {
	Type type;
	Format format;
	std::variant<std::filesystem::path, std::string> data;
};

} // namespace void_engine::resource::shader
