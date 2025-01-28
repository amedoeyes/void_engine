export module void_engine.graphics:shader_enums;

import std;

export namespace void_engine::graphics {

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

} // namespace void_engine::graphics
