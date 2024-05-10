#ifndef VOID_ENGINE_RENDERER_RENDERER_HPP
#define VOID_ENGINE_RENDERER_RENDERER_HPP

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <glm/glm.hpp>

#include "common.hpp"

namespace void_engine::renderer {

class Renderer {
	public:
	static void init();

	static void clear();
	static void draw_arrays(PrimitiveType type, int first, int count);
	static void draw_elements(
		PrimitiveType type, int count, DataType indices_type,
		const void* indices
	);

	static void set_clear_color(glm::vec4 color);
	static void set_viewport(glm::vec2 pos, glm::vec2 size);
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

	private:
	static bool _depth_test;
	static bool _blend;
	static bool _stencil;

	private:
	static APIENTRY void debug_message_callback(
		unsigned int source, unsigned int type, unsigned int id,
		unsigned int severity, int length, const char* message,
		const void* user_param
	);
};

}  // namespace void_engine::renderer

#endif	// !VOID_ENGINE_RENDERER_RENDERER_HPP
