export module void_engine.graphics:shader_source;

import :shader_enums;

import std;

export namespace void_engine::graphics {

struct ShaderSource {
	ShaderType type;
	ShaderFormat format;
	std::variant<std::filesystem::path, std::span<const std::byte>> data;
};

} // namespace void_engine::graphics
