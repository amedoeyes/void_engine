#ifndef VOID_ENGINE_GRAPHICS_RENDERER_RENDERER_HPP
#define VOID_ENGINE_GRAPHICS_RENDERER_RENDERER_HPP

#include "void_engine/graphics/buffer/uniform_buffer.hpp"
#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"
#include "void_engine/resource/shader/shader.hpp"
#include "void_engine/utility/bit_mask.hpp"
#include "void_engine/utility/transform.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>

namespace void_engine::graphics::renderer {

struct CameraUniform {
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 view_projection;
};

class Renderer {
public:
	static void init();
	static void update();
	static void terminate();

	static void clear();

	static void draw_mesh(const Mesh& mesh);
	static void draw_mesh_instanced(const Mesh& mesh, unsigned int instances);
	static void draw_point(const glm::vec3& position, float size, const glm::vec4& color);
	static void draw_line(
		const glm::vec3& start, const glm::vec3& end, float width, const glm::vec4& color
	);
	static void draw_quad(const utility::Transform& transform, const glm::vec4& color);
	static void draw_quad_outline(
		const utility::Transform& transform, float width, const glm::vec4& color
	);
	static void draw_circle(const utility::Transform& transform, const glm::vec4& color);
	static void draw_circle_outline(
		const utility::Transform& transform, float width, const glm::vec4& color
	);
	static void draw_cube(const utility::Transform& transform, const glm::vec4& color);
	static void draw_cube_outline(
		const utility::Transform& transform, float width, const glm::vec4& color
	);
	static void draw_elements(PrimitiveType type, unsigned int count, void* indices);
	static void draw_elements_instanced(
		PrimitiveType type, unsigned int count, void* indices, unsigned int instances
	);

	static void set_clear_color(const glm::vec4& color);
	static void set_viewport(const glm::ivec2& position, const glm::ivec2& size);
	static void set_viewport_position(const glm::ivec2& position);
	static void set_viewport_size(const glm::ivec2& size);
	static void set_point_size(float size);
	static void set_line_width(float width);
	static void set_depth_test(bool enabled);
	static void set_depth_func(DepthFunc func);
	static void set_blend(bool enabled);
	static void set_blend_func(BlendFunc src, BlendFunc dst);
	static void set_blend_equation(BlendEquation eq);
	static void set_stencil(bool enabled);
	static void set_stencil_mask(unsigned int mask);
	static void set_stencil_func(StencilFunc func, int ref, unsigned int mask);
	static void set_stencil_op(StencilOp sfail, StencilOp dpfail, StencilOp dppass);
	static void set_cull_face(bool enabled);
	static void set_cull_face(CullFace face);
	static void set_front_face(FrontFace face);
	static void set_polygon_mode(PolygonMode mode);
	static void set_camera(camera::Camera& camera);

	static auto get_clear_color() -> const glm::vec4&;
	static auto get_viewport_size() -> const glm::ivec2&;
	static auto get_viewport_position() -> const glm::ivec2&;
	static auto is_blend_enabled() -> bool;
	static auto get_blend_func() -> std::pair<BlendFunc, BlendFunc>;
	static auto get_blend_equation() -> BlendEquation;
	static auto is_stencil_enabled() -> bool;
	static auto get_stencil_mask() -> unsigned int;
	static auto get_stencil_func() -> std::tuple<StencilFunc, int, unsigned int>;
	static auto get_stencil_op() -> std::tuple<StencilOp, StencilOp, StencilOp>;
	static auto is_cull_face_enabled() -> bool;
	static auto get_cull_face() -> CullFace;
	static auto get_front_face() -> FrontFace;
	static auto get_polygon_mode() -> PolygonMode;
	static auto get_camera() -> camera::Camera&;

private:
	static inline glm::ivec2 _viewport_position;
	static inline glm::ivec2 _viewport_size;
	static inline utility::BitMask<ClearFlags> _clear_flags;
	static inline camera::Camera* _camera = nullptr;
	static inline buffer::UniformBuffer<CameraUniform>* _camera_uniform = nullptr;
	static inline camera::Camera* _default_camera = nullptr;
	static inline resource::Shader* _shape_shader = nullptr;

	static void update_camera_viewport();
	static void update_camera_uniform();
};

} // namespace void_engine::graphics::renderer

#endif // !VOID_ENGINE_GRAPHICS_RENDERER_RENDERER_HPP
