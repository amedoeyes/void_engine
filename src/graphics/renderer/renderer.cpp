#include "void_engine/graphics/renderer/renderer.hpp"

#include "void_engine/graphics/buffer/enums.hpp"
#include "void_engine/graphics/buffer/uniform_buffer.hpp"
#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/graphics/camera/perspective_camera.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"
#include "void_engine/resource/font/font.hpp"
#include "void_engine/resource/font/text.hpp"
#include "void_engine/resource/resource_manager.hpp"
#include "void_engine/resource/shader/enums.hpp"
#include "void_engine/resource/shader/shader.hpp"
#include "void_engine/utility/bit_mask.hpp"
#include "void_engine/utility/logger.hpp"
#include "void_engine/utility/transform.hpp"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <span>
#include <string>
#include <string_view>
#include <utility>

namespace void_engine::graphics::renderer {

namespace {

APIENTRY void debug_message_callback(
	unsigned int source, unsigned int type, unsigned int /*unused*/, unsigned int severity,
	int /*unused*/, const char* message, const void* /*unused*/
) {
	std::string source_str;
	std::string type_str;
	switch (source) {
		case GL_DEBUG_SOURCE_API: source_str = "API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: source_str = "Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: source_str = "Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY: source_str = "Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION: source_str = "Application"; break;
		case GL_DEBUG_SOURCE_OTHER: source_str = "Other"; break;
		default: std::unreachable();
	}
	switch (type) {
		case GL_DEBUG_TYPE_ERROR: type_str = "Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: type_str = "Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY: type_str = "Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE: type_str = "Performance"; break;
		case GL_DEBUG_TYPE_MARKER: type_str = "Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP: type_str = "Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP: type_str = "Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER: type_str = "Other"; break;
		default: std::unreachable();
	}
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			utility::logger::error("OpenGL: {}: {}: {}", source_str, type_str, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_LOW:
			utility::logger::warning("OpenGL: {}: {}: {}", source_str, type_str, message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			utility::logger::info("OpenGL: {}: {}: {}", source_str, type_str, message);
			break;
		default: std::unreachable();
	}
}

// NOLINTNEXTLINE
constexpr unsigned char shape_shader_vert[] = {
#include "shape.vert.spv.h"
};

// NOLINTNEXTLINE
constexpr unsigned char shape_shader_frag[] = {
#include "shape.frag.spv.h"
};

// NOLINTNEXTLINE
constexpr unsigned char font_shader_vert[] = {
#include "font.vert.spv.h"
};

// NOLINTNEXTLINE
constexpr unsigned char font_screen_shader_vert[] = {
#include "font_screen.vert.spv.h"
};

// NOLINTNEXTLINE
constexpr unsigned char font_shader_frag[] = {
#include "font.frag.spv.h"
};

// NOLINTNEXTLINE
constexpr unsigned char liberation_font[] = {
#include "liberation.ttf.h"
};

} // namespace

Renderer::Renderer() {
	int flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if ((static_cast<unsigned int>(flags) & GL_CONTEXT_FLAG_DEBUG_BIT) != 0) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_message_callback, nullptr);
	}

	_default_camera = _camera = new camera::PerspectiveCamera();

	_camera_uniform.bind_range(0);
	_camera_uniform.allocate(sizeof(CameraUniform), buffer::Usage::dynamic_draw);

	resource::shader::Shader& shape_shader = _resource_manager.shaders().create("shape");
	shape_shader.add_source(
		resource::shader::Type::vertex,
		std::as_bytes(std::span(shape_shader_vert)),
		resource::shader::Format::spirv
	);
	shape_shader.add_source(
		resource::shader::Type::fragment,
		std::as_bytes(std::span(shape_shader_frag)),
		resource::shader::Format::spirv
	);
	shape_shader.compile();

	resource::shader::Shader& font_shader = _resource_manager.shaders().create("font");
	font_shader.add_source(
		resource::shader::Type::vertex,
		std::as_bytes(std::span(font_shader_vert)),
		resource::shader::Format::spirv
	);
	font_shader.add_source(
		resource::shader::Type::fragment,
		std::as_bytes(std::span(font_shader_frag)),
		resource::shader::Format::spirv
	);
	font_shader.compile();

	resource::shader::Shader& font_screen_shader = _resource_manager.shaders().create("font_screen");
	font_screen_shader.add_source(
		resource::shader::Type::vertex,
		std::as_bytes(std::span(font_screen_shader_vert)),
		resource::shader::Format::spirv
	);
	font_screen_shader.add_source(
		resource::shader::Type::fragment,
		std::as_bytes(std::span(font_shader_frag)),
		resource::shader::Format::spirv
	);
	font_screen_shader.compile();

	const resource::font::Font& font =
		_resource_manager.fonts().create("liberation", std::as_bytes(std::span(liberation_font)));

	_draw_objects.text.set_font(font);
}

Renderer::~Renderer() {
	delete _default_camera;
}

void Renderer::clear() const {
	glClear(_clear.flags.get());
}

void Renderer::update() {
	update_camera_uniform();
	clear();
}

void Renderer::draw_point(const glm::vec3& position, float size, const glm::vec4& color) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, glm::translate(glm::mat4(1.0f), position));
	shader.set_uniform(1, color);
	shader.bind();
	set_point_size(size);
	draw_mesh(_draw_objects.point);
}

void Renderer::draw_line(
	const glm::vec3& start, const glm::vec3& end, float width, const glm::vec4& color
) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	const glm::vec3 direction = end - start;
	const glm::vec3 normal = glm::normalize(direction);
	const glm::vec3 reference(1.0f, 0.0f, 0.0f);
	const float cos_theta = glm::dot(reference, normal);
	glm::vec3 axis;
	float angle = 0;
	if (cos_theta > 0.9999f) {
		axis = {0.0f, 0.0f, 1.0f};
		angle = 0.0f;
	} else if (cos_theta < -0.9999f) {
		axis = glm::abs(reference.x) > 0.1f ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		angle = glm::pi<float>();
	} else {
		axis = glm::normalize(glm::cross(reference, normal));
		angle = std::acos(cos_theta);
	}
	utility::Transform transform;
	transform.set_position(start + direction * 0.5f);
	transform.set_rotation(angle, axis);
	transform.set_scale({glm::length(direction) * 0.5f, 1.0f, 1.0f});
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(_draw_objects.line);
}

void Renderer::draw_quad(const utility::Transform& transform, const glm::vec4& color) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	draw_mesh(_draw_objects.quad);
}

void Renderer::draw_quad_outline(
	const utility::Transform& transform, float width, const glm::vec4& color
) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(_draw_objects.quad_outline);
}

void Renderer::draw_circle(const utility::Transform& transform, const glm::vec4& color) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	draw_mesh(_draw_objects.circle);
}

void Renderer::draw_circle_outline(
	const utility::Transform& transform, float width, const glm::vec4& color
) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(_draw_objects.circle_outline);
}

void Renderer::draw_cube(const utility::Transform& transform, const glm::vec4& color) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	draw_mesh(_draw_objects.cube);
}

void Renderer::draw_cube_outline(
	const utility::Transform& transform, float width, const glm::vec4& color
) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(_draw_objects.cube_outline);
}

void Renderer::draw_text(
	const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("font");
	const Blend prev_blend = get_blend();
	set_blend_enabled(true);
	set_blend_factors({BlendFactor::src_alpha, BlendFactor::one_minus_src_alpha});
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(2, color);
	shader.bind();
	text.get_font().get_texture().bind_unit(0);
	draw_mesh(text.get_mesh());
	set_blend_enabled(prev_blend.enabled);
	set_blend_factors(prev_blend.factors);
}

void Renderer::draw_text(
	std::string_view text, const utility::Transform& transform, const glm::vec4& color
) {
	_draw_objects.text.set_data(text);
	draw_text(_draw_objects.text, transform, color);
}

void Renderer::draw_text_screen(
	const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
) {
	const resource::shader::Shader& shader = _resource_manager.shaders().get("font_screen");
	const Blend prev_blend = get_blend();
	set_blend_enabled(true);
	set_blend_factors({BlendFactor::src_alpha, BlendFactor::one_minus_src_alpha});
	text.get_font().get_texture().bind_unit(0);
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, _screen_projection);
	shader.set_uniform(2, color);
	shader.bind();
	draw_mesh(text.get_mesh());
	set_blend_enabled(prev_blend.enabled);
	set_blend_factors(prev_blend.factors);
}

void Renderer::draw_text_screen(
	std::string_view text, const utility::Transform& transform, const glm::vec4& color
) {
	_draw_objects.text.set_data(text);
	draw_text_screen(_draw_objects.text, transform, color);
}

void Renderer::draw_mesh(const Mesh& mesh) {
	mesh.bind();
	draw_elements(mesh.get_primitive_type(), mesh.get_count(), nullptr);
}

void Renderer::draw_mesh_instanced(const Mesh& mesh, unsigned int instances) {
	mesh.bind();
	draw_elements_instanced(mesh.get_primitive_type(), mesh.get_count(), nullptr, instances);
}

void Renderer::draw_elements(PrimitiveType type, unsigned int count, void* indices) {
	glDrawElements(static_cast<GLenum>(type), static_cast<GLsizei>(count), GL_UNSIGNED_INT, indices);
}

void Renderer::draw_elements_instanced(
	PrimitiveType type, unsigned int count, void* indices, unsigned int instances
) {
	glDrawElementsInstanced(
		static_cast<GLenum>(type),
		static_cast<GLsizei>(count),
		GL_UNSIGNED_INT,
		indices,
		static_cast<GLsizei>(instances)
	);
}

void Renderer::set_camera(camera::Camera& camera) {
	_camera = &camera;
	_camera->set_size(get_viewport().size);
}

void Renderer::set_clear_color(const glm::vec4& color) {
	glClearColor(color.r, color.g, color.b, color.a);
	_clear.color = color;
}

void Renderer::set_polygon_mode(PolygonMode mode) {
	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
	_polygon_mode = mode;
}

void Renderer::set_blend(const Blend& blend) {
	set_blend_enabled(blend.enabled);
	set_blend_factors(blend.factors);
	set_blend_equation(blend.equation);
}

void Renderer::set_blend_enabled(bool enabled) {
	set_enabled(GL_BLEND, enabled);
	_blend.enabled = enabled;
}

void Renderer::set_blend_factors(const BlendFactors& factors) {
	glBlendFunc(static_cast<GLenum>(factors.source), static_cast<GLenum>(factors.destination));
	_blend.factors = factors;
}

void Renderer::set_blend_equation(BlendEquation equation) {
	glBlendEquation(static_cast<GLenum>(equation));
	_blend.equation = equation;
}

void Renderer::set_cull_face(const CullFace& cull_face) {
	set_cull_face_enabled(cull_face.enabled);
	set_cull_face_facet(cull_face.facet);
	set_cull_face_orientation(cull_face.orientation);
}

void Renderer::set_cull_face_enabled(bool enabled) {
	set_enabled(GL_CULL_FACE, enabled);
	_cull_face.enabled = enabled;
}

void Renderer::set_cull_face_facet(CullFaceFacet facet) {
	glCullFace(static_cast<GLenum>(facet));
	_cull_face.facet = facet;
}

void Renderer::set_cull_face_orientation(CullFaceOrientation orientation) {
	glFrontFace(static_cast<GLenum>(orientation));
	_cull_face.orientation = orientation;
}

void Renderer::set_depth(const Depth& depth) {
	set_depth_enabled(depth.enabled);
	set_depth_function(depth.function);
}

void Renderer::set_depth_enabled(bool enabled) {
	set_enabled(GL_DEPTH_TEST, enabled);
	_depth.enabled = enabled;
	_clear.flags.set(ClearFlags::depth, enabled);
}

void Renderer::set_depth_function(DepthFunction function) {
	glDepthFunc(static_cast<GLenum>(function));
	_depth.function = function;
}

void Renderer::set_stencil(const Stencil& stencil) {
	set_stencil_enabled(stencil.enabled);
	set_stencil_settings(stencil.settings);
	set_stencil_actions(stencil.actions);
}

void Renderer::set_stencil_enabled(bool enabled) {
	set_enabled(GL_STENCIL_TEST, enabled);
	_stencil.enabled = enabled;
	_clear.flags.set(ClearFlags::stencil, enabled);
}

void Renderer::set_stencil_settings(const StencilSettings& settings) {
	glStencilFunc(static_cast<GLenum>(settings.function), settings.reference, settings.mask);
	_stencil.settings = settings;
}

void Renderer::set_stencil_actions(const StencilActions& actions) {
	glStencilOp(
		static_cast<GLenum>(actions.stencil_fail),
		static_cast<GLenum>(actions.depth_fail),
		static_cast<GLenum>(actions.depth_pass)
	);
	_stencil.actions = actions;
}

void Renderer::set_viewport(const Viewport& viewport) {
	assert(viewport.size.x >= 0 && viewport.size.y >= 0 && "Viewport size must be positive");
	glViewport(viewport.position.x, viewport.position.y, viewport.size.x, viewport.size.y);
	_viewport = viewport;
	_screen_projection = glm::ortho(
		0.0f, static_cast<float>(viewport.size.x), 0.0f, static_cast<float>(viewport.size.y)
	);
	_camera->set_size(viewport.size);
}

void Renderer::set_viewport_position(const glm::ivec2& position) {
	set_viewport({position, get_viewport().size});
}

void Renderer::set_viewport_size(const glm::ivec2& size) {
	set_viewport({get_viewport().position, size});
}

void Renderer::set_point_size(float size) {
	glPointSize(size);
}

void Renderer::set_line_width(float width) {
	glLineWidth(width);
}

auto Renderer::get_camera() const -> camera::Camera& {
	return *_camera;
}

auto Renderer::get_clear_color() const -> const glm::vec4& {
	return _clear.color;
}

auto Renderer::get_polygon_mode() const -> PolygonMode {
	return _polygon_mode;
}

auto Renderer::get_blend() const -> const Blend& {
	return _blend;
}

auto Renderer::get_cull_face() const -> const CullFace& {
	return _cull_face;
}

auto Renderer::get_depth() const -> const Depth& {
	return _depth;
}

auto Renderer::get_stencil() const -> const Stencil& {
	return _stencil;
}

auto Renderer::get_viewport() const -> const Viewport& {
	return _viewport;
}

void Renderer::update_camera_uniform() {
	const glm::mat4& projection = _camera->get_projection();
	const glm::mat4& view = _camera->get_view();
	const glm::mat4& view_projection = _camera->get_view_projection();
	const CameraUniform& uniform_data = _camera_uniform.get_data();
	if (projection != uniform_data.projection) {
		_camera_uniform.set_sub_data(offsetof(CameraUniform, projection), projection);
	}
	if (view != uniform_data.view) {
		_camera_uniform.set_sub_data(offsetof(CameraUniform, view), view);
	}
	if (view_projection != uniform_data.view_projection) {
		_camera_uniform.set_sub_data(offsetof(CameraUniform, view_projection), view_projection);
	}
}

void Renderer::set_enabled(unsigned int capability, bool enabled) {
	(enabled ? glEnable : glDisable)(capability);
}

} // namespace void_engine::graphics::renderer
