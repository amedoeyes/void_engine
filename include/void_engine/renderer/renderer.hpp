#ifndef VOID_ENGINE_RENDERER_RENDERER_HPP
#define VOID_ENGINE_RENDERER_RENDERER_HPP

#include "void_engine/renderer/camera/camera.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>

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

class Renderer {
public:
	static void init();

public:
	static void clear();
	static void draw_arrays(PrimitiveType type, int first, int count);
	static void draw_elements(
		PrimitiveType type, unsigned int count, void* indices
	);

	static void set_clear_color(glm::vec4 color);
	static void set_viewport(glm::vec2 pos, glm::vec2 size);
	static void set_viewport_pos(glm::vec2 pos);
	static void set_viewport_size(glm::vec2 size);
	static void set_depth_test(bool enabled);
	static void set_depth_func(DepthFunc func);
	static void set_blend(bool enabled);
	static void set_blend_func(BlendFunc src, BlendFunc dst);
	static void set_blend_equation(BlendEquation eq);
	static void set_stencil(bool enabled);
	static void set_stencil_mask(unsigned int mask);
	static void set_stencil_func(StencilFunc func, int ref, unsigned int mask);
	static void set_stencil_op(
		StencilOp sfail, StencilOp dpfail, StencilOp dppass
	);
	static void set_cull_face(bool enabled);
	static void set_cull_face(CullFace face);
	static void set_front_face(FrontFace face);
	static void set_polygon_mode(PolygonMode mode);
	static void set_camera(camera::Camera* camera);

	static auto get_clear_color() -> glm::vec4;
	static auto get_viewport_size() -> glm::vec2;
	static auto get_viewport_pos() -> glm::vec2;
	static auto get_camera() -> camera::Camera*;

private:
	static glm::vec4 _clear_color;
	static glm::vec2 _viewport_pos;
	static glm::vec2 _viewport_size;
	static bool _depth_test;
	static bool _blend;
	static bool _stencil;
	static camera::Camera* _camera;

private:
	static APIENTRY void debug_message_callback(
		unsigned int source, unsigned int type, unsigned int id,
		unsigned int severity, int length, const char* message,
		const void* user_param
	);
};

} // namespace void_engine::renderer

#endif // !VOID_ENGINE_RENDERER_RENDERER_HPP
