#ifndef VOID_ENGINE_RENDERER_RENDERER_HPP
#define VOID_ENGINE_RENDERER_RENDERER_HPP

#include "void_engine/renderer/camera/camera.hpp"
#include "void_engine/renderer/common.hpp"

#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float4.hpp>

namespace void_engine::renderer {

class Renderer {
public:
	static void init();

	static void clear();
	static void draw_arrays(PrimitiveType type, int first, int count);
	static void
	draw_elements(PrimitiveType type, unsigned int count, void* indices);

	static void set_clear_color(glm::vec4 color);
	static void set_viewport(glm::vec<2, int> pos, glm::vec<2, int> size);
	static void set_depth_test(bool enabled);
	static void set_depth_func(DepthFunc func);
	static void set_blend(bool enabled);
	static void set_blend_func(BlendFunc src, BlendFunc dst);
	static void set_blend_equation(BlendEquation eq);
	static void set_stencil(bool enabled);
	static void set_stencil_mask(unsigned int mask);
	static void set_stencil_func(StencilFunc func, int ref, unsigned int mask);
	static void
	set_stencil_op(StencilOp sfail, StencilOp dpfail, StencilOp dppass);
	static void set_cull_face(bool enabled);
	static void set_cull_face(CullFace face);
	static void set_front_face(FrontFace face);
	static void set_polygon_mode(PolygonMode mode);

	static void set_camera(camera::Camera* camera);
	static auto get_camera() -> camera::Camera*;

private:
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
