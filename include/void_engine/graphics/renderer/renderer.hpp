#ifndef VOID_ENGINE_GRAPHICS_RENDERER_RENDERER_HPP
#define VOID_ENGINE_GRAPHICS_RENDERER_RENDERER_HPP

#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"
#include "void_engine/resource/font/text.hpp"
#include "void_engine/utility/transform.hpp"

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <string_view>
#include <tuple>
#include <utility>

namespace void_engine::graphics::renderer {

void init();
void update();
void terminate();

void clear();

void draw_mesh(const Mesh& mesh);
void draw_mesh_instanced(const Mesh& mesh, unsigned int instances);
void draw_point(const glm::vec3& position, float size, const glm::vec4& color);
void draw_line(const glm::vec3& start, const glm::vec3& end, float width, const glm::vec4& color);
void draw_quad(const utility::Transform& transform, const glm::vec4& color);
void draw_quad_outline(const utility::Transform& transform, float width, const glm::vec4& color);
void draw_circle(const utility::Transform& transform, const glm::vec4& color);
void draw_circle_outline(const utility::Transform& transform, float width, const glm::vec4& color);
void draw_cube(const utility::Transform& transform, const glm::vec4& color);
void draw_cube_outline(const utility::Transform& transform, float width, const glm::vec4& color);
void draw_elements(PrimitiveType type, unsigned int count, void* indices);
void draw_elements_instanced(
	PrimitiveType type, unsigned int count, void* indices, unsigned int instances
);
void draw_text(
	const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
);
void draw_text(std::string_view text, const utility::Transform& transform, const glm::vec4& color);
void draw_text_screen(
	const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
);
void draw_text_screen(
	std::string_view text, const utility::Transform& transform, const glm::vec4& color
);

void set_clear_color(const glm::vec4& color);
void set_viewport(const glm::ivec2& position, const glm::ivec2& size);
void set_viewport_position(const glm::ivec2& position);
void set_viewport_size(const glm::ivec2& size);
void set_point_size(float size);
void set_line_width(float width);
void set_depth_test(bool enabled);
void set_depth_func(DepthFunc func);
void set_blend(bool enabled);
void set_blend_func(BlendFunc src, BlendFunc dst);
void set_blend_equation(BlendEquation eq);
void set_stencil(bool enabled);
void set_stencil_mask(unsigned int mask);
void set_stencil_func(StencilFunc func, int ref, unsigned int mask);
void set_stencil_op(StencilOp sfail, StencilOp dpfail, StencilOp dppass);
void set_cull_face(bool enabled);
void set_cull_face(CullFace face);
void set_front_face(FrontFace face);
void set_polygon_mode(PolygonMode mode);
void set_camera(camera::Camera& camera);

auto get_clear_color() -> const glm::vec4&;
auto get_viewport_size() -> const glm::ivec2&;
auto get_viewport_position() -> const glm::ivec2&;
auto is_blend_enabled() -> bool;
auto get_blend_func() -> std::pair<BlendFunc, BlendFunc>;
auto get_blend_equation() -> BlendEquation;
auto is_stencil_enabled() -> bool;
auto get_stencil_mask() -> unsigned int;
auto get_stencil_func() -> std::tuple<StencilFunc, int, unsigned int>;
auto get_stencil_op() -> std::tuple<StencilOp, StencilOp, StencilOp>;
auto is_cull_face_enabled() -> bool;
auto get_cull_face() -> CullFace;
auto get_front_face() -> FrontFace;
auto get_polygon_mode() -> PolygonMode;
auto get_camera() -> camera::Camera&;

} // namespace void_engine::graphics::renderer

#endif // !VOID_ENGINE_GRAPHICS_RENDERER_RENDERER_HPP
