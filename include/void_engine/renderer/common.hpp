#ifndef VOID_ENGINE_RENDERER_COMMON_HPP
#define VOID_ENGINE_RENDERER_COMMON_HPP

#include <glad/gl.h>

namespace void_engine::renderer {

enum class PrimitiveType {
	points = GL_POINTS,
	line_strip = GL_LINE_STRIP,
	line_loop = GL_LINE_LOOP,
	lines = GL_LINES,
	line_strip_adjacency = GL_LINE_STRIP_ADJACENCY,
	lines_adjacency = GL_LINES_ADJACENCY,
	triangle_strip = GL_TRIANGLE_STRIP,
	triangle_fan = GL_TRIANGLE_FAN,
	triangles = GL_TRIANGLES,
	triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	triangles_adjacency = GL_TRIANGLES_ADJACENCY,
	patches = GL_PATCHES
};

enum class DepthFunc {
	never = GL_NEVER,
	less = GL_LESS,
	equal = GL_EQUAL,
	lequal = GL_LEQUAL,
	greater = GL_GREATER,
	notequal = GL_NOTEQUAL,
	gequal = GL_GEQUAL,
	always = GL_ALWAYS,
};

enum class BlendFunc {
	zero = GL_ZERO,
	one = GL_ONE,
	src_color = GL_SRC_COLOR,
	one_minus_src_color = GL_ONE_MINUS_SRC_COLOR,
	dst_color = GL_DST_COLOR,
	one_minus_dst_color = GL_ONE_MINUS_DST_COLOR,
	src_alpha = GL_SRC_ALPHA,
	one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
	dst_alpha = GL_DST_ALPHA,
	one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA,
	constant_color = GL_CONSTANT_COLOR,
	one_minus_constant_color = GL_ONE_MINUS_CONSTANT_COLOR,
	constant_alpha = GL_CONSTANT_ALPHA,
	one_minus_constant_alpha = GL_ONE_MINUS_CONSTANT_ALPHA,
};

enum class BlendEquation {
	add = GL_FUNC_ADD,
	subtract = GL_FUNC_SUBTRACT,
	reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
	min = GL_MIN,
	max = GL_MAX,
};

enum class StencilFunc {
	never = GL_NEVER,
	less = GL_LESS,
	equal = GL_EQUAL,
	lequal = GL_LEQUAL,
	greater = GL_GREATER,
	notequal = GL_NOTEQUAL,
	gequal = GL_GEQUAL,
	always = GL_ALWAYS,
};

enum class StencilOp {
	keep = GL_KEEP,
	zero = GL_ZERO,
	replace = GL_REPLACE,
	increment = GL_INCR,
	increment_wrap = GL_INCR_WRAP,
	decrement = GL_DECR,
	decrement_wrap = GL_DECR_WRAP,
	invert = GL_INVERT,
};

enum class StencilFace {
	front = GL_FRONT,
	back = GL_BACK,
	front_and_back = GL_FRONT_AND_BACK,
};

enum class CullFace {
	front = GL_FRONT,
	back = GL_BACK,
	front_and_back = GL_FRONT_AND_BACK,
};

enum class FrontFace {
	clockwise = GL_CW,
	counter_clockwise = GL_CCW,
};

enum class PolygonMode {
	fill = GL_FILL,
	line = GL_LINE,
	point = GL_POINT,
};

enum class BufferTarget {
	array = GL_ARRAY_BUFFER,
	atomic_counter = GL_ATOMIC_COUNTER_BUFFER,
	copy_read = GL_COPY_READ_BUFFER,
	copy_write = GL_COPY_WRITE_BUFFER,
	dispatch_indirect = GL_DISPATCH_INDIRECT_BUFFER,
	draw_indirect = GL_DRAW_INDIRECT_BUFFER,
	element_array = GL_ELEMENT_ARRAY_BUFFER,
	pixel_pack = GL_PIXEL_PACK_BUFFER,
	pixel_unpack = GL_PIXEL_UNPACK_BUFFER,
	query = GL_QUERY_BUFFER,
	shader_storage = GL_SHADER_STORAGE_BUFFER,
	texture = GL_TEXTURE_BUFFER,
	transform_feedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	uniform = GL_UNIFORM_BUFFER
};

enum class BufferUsage {
	stream_draw = GL_STREAM_DRAW,
	stream_read = GL_STREAM_READ,
	stream_copy = GL_STREAM_COPY,
	static_draw = GL_STATIC_DRAW,
	static_read = GL_STATIC_READ,
	static_copy = GL_STATIC_COPY,
	dynamic_draw = GL_DYNAMIC_DRAW,
	dynamic_read = GL_DYNAMIC_READ,
	dynamic_copy = GL_DYNAMIC_COPY
};

enum class ShaderType {
	compute = GL_COMPUTE_SHADER,
	vertex = GL_VERTEX_SHADER,
	tess_control = GL_TESS_CONTROL_SHADER,
	tess_evaluation = GL_TESS_EVALUATION_SHADER,
	geometry = GL_GEOMETRY_SHADER,
	fragment = GL_FRAGMENT_SHADER
};

}  // namespace void_engine::renderer

#endif	// !VOID_ENGINE_RENDERER_COMMON_HPP
