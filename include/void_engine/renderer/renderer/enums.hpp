#ifndef VOID_ENGINE_RENDERER_ENUMS_HPP
#define VOID_ENGINE_RENDERER_ENUMS_HPP

#include <cstdint>

namespace void_engine::renderer {

enum class PrimitiveType : uint8_t {
	points = 0x0000,
	line_strip = 0x0003,
	line_loop = 0x0002,
	lines = 0x0001,
	line_strip_adjacency = 0x000B,
	lines_adjacency = 0x000A,
	triangle_strip = 0x0005,
	triangle_fan = 0x0006,
	triangles = 0x0004,
	triangle_strip_adjacency = 0x000D,
	triangles_adjacency = 0x000C,
	patches = 0x000E
};

enum class DepthFunc : uint16_t {
	never = 0x0200,
	less = 0x0201,
	equal = 0x0202,
	lequal = 0x0203,
	greater = 0x0204,
	notequal = 0x0205,
	gequal = 0x0206,
	always = 0x0207,
};

enum class BlendFunc : uint16_t {
	zero = 0,
	one = 1,
	src_color = 0x0300,
	one_minus_src_color = 0x0301,
	dst_color = 0x0306,
	one_minus_dst_color = 0x0307,
	src_alpha = 0x0302,
	one_minus_src_alpha = 0x0303,
	dst_alpha = 0x0304,
	one_minus_dst_alpha = 0x0305,
	constant_color = 0x8001,
	one_minus_constant_color = 0x8002,
	constant_alpha = 0x8003,
	one_minus_constant_alpha = 0x8004,
};

enum class BlendEquation : uint16_t {
	add = 0x8006,
	subtract = 0x800A,
	reverse_subtract = 0x800B,
	min = 0x8007,
	max = 0x8008,
};

enum class StencilFunc : uint16_t {
	never = 0x0200,
	less = 0x0201,
	equal = 0x0202,
	lequal = 0x0203,
	greater = 0x0204,
	notequal = 0x0205,
	gequal = 0x0206,
	always = 0x0207,
};

enum class StencilOp : uint16_t {
	keep = 0x1E00,
	zero = 0,
	replace = 0x1E01,
	increment = 0x1E02,
	increment_wrap = 0x8507,
	decrement = 0x1E03,
	decrement_wrap = 0x8508,
	invert = 0x150A,
};

enum class StencilFace : uint16_t {
	front = 0x0404,
	back = 0x0405,
	front_and_back = 0x0408,
};

enum class CullFace : uint16_t {
	front = 0x0404,
	back = 0x0405,
	front_and_back = 0x0408,
};

enum class FrontFace : uint16_t {
	clockwise = 0x0900,
	counter_clockwise = 0x0901,
};

enum class PolygonMode : uint16_t {
	fill = 0x1B02,
	line = 0x1B01,
	point = 0x1B00,
};

enum class ClearFlags : uint16_t {
	color = 0x00004000,
	depth = 0x00000100,
	stencil = 0x00000400,
};

} // namespace void_engine::renderer

#endif // VOID_ENGINE_RENDERER_ENUMS_HPP
