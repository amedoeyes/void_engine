#include "void_engine/renderer/renderer/renderer.hpp"

#include "void_engine/renderer/buffer/buffer.hpp"
#include "void_engine/renderer/buffer/uniform_buffer.hpp"
#include "void_engine/renderer/camera/camera.hpp"
#include "void_engine/renderer/camera/orthographic_camera.hpp"
#include "void_engine/renderer/camera/perspective_camera.hpp"
#include "void_engine/renderer/geometry/circle.hpp"
#include "void_engine/renderer/geometry/cube.hpp"
#include "void_engine/renderer/geometry/line.hpp"
#include "void_engine/renderer/geometry/point.hpp"
#include "void_engine/renderer/geometry/quad.hpp"
#include "void_engine/renderer/mesh.hpp"
#include "void_engine/renderer/renderer/enums.hpp"
#include "void_engine/resource/shader/shader.hpp"
#include "void_engine/utility/bit_mask.hpp"
#include "void_engine/utility/logger.hpp"
#include "void_engine/utility/transform.hpp"

#include <cassert>
#include <cstddef>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <string>
#include <string_view>

namespace void_engine::renderer {

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
		default:;
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
		default:;
	}
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			utility::Logger::error("OpenGL: {}: {}: {}", source_str, type_str, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_LOW:
			utility::Logger::warning("OpenGL: {}: {}: {}", source_str, type_str, message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			utility::Logger::info("OpenGL: {}: {}: {}", source_str, type_str, message);
			break;
		default:;
	}
}

constexpr std::string_view shape_vertex_shader = R"glsl(
#version 460 core
layout(location = 0) in vec3 i_position;
layout(binding = 0) uniform Camera {
	mat4 projection;
	mat4 view;
	mat4 view_projection;
} u_camera;
uniform mat4 u_model;
void main() {
	gl_Position = u_camera.view_projection *  u_model * vec4(i_position, 1.0);
}
)glsl";

constexpr std::string_view shape_fragment_shader = R"glsl(
#version 460 core
uniform vec4 u_color;
out vec4 o_color;
void main() {
	o_color = u_color;
}
)glsl";

} // namespace

void Renderer::init() {
	if (gladLoadGL() == 0) {
		assert(false && "Failed to initialize GLAD");
	}

	int flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if ((static_cast<unsigned int>(flags) & GL_CONTEXT_FLAG_DEBUG_BIT) != 0) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_message_callback, nullptr);
	}

	_clear_flags.set(ClearFlags::color);

	_default_camera = new camera::PerspectiveCamera();
	_default_camera->set_position({0.0f, 0.0f, 1.0f});

	_camera = _default_camera;
	_camera_uniform = new buffer::UniformBuffer<CameraUniform>();
	_camera_uniform->bind_range(0);
	_camera_uniform->allocate(sizeof(CameraUniform), buffer::BufferUsage::dynamic_draw);

	_shape_shader = new resource::Shader();
	_shape_shader->add_source(resource::ShaderType::vertex, shape_vertex_shader);
	_shape_shader->add_source(resource::ShaderType::fragment, shape_fragment_shader);
	_shape_shader->compile();
}

void Renderer::update() {
	update_camera_uniform();
	clear();
}

void Renderer::terminate() {
	delete _default_camera;
	delete _camera_uniform;
	delete _shape_shader;
}

void Renderer::clear() {
	glClear(_clear_flags.get());
}

void Renderer::draw_mesh(const Mesh& mesh) {
	mesh.bind();
	draw_elements(mesh.get_primitive_type(), mesh.get_count(), nullptr);
}

void Renderer::draw_mesh_instanced(const Mesh& mesh, unsigned int instances) {
	mesh.bind();
	draw_elements_instanced(mesh.get_primitive_type(), mesh.get_count(), nullptr, instances);
}

void Renderer::draw_point(const glm::vec3& position, float size, const glm::vec4& color) {
	static const Mesh point = geometry::create_point_mesh();
	_shape_shader->set_uniform("u_model", glm::translate(glm::mat4(1.0f), position));
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	set_point_size(size);
	draw_mesh(point);
}

void Renderer::draw_line(
	const glm::vec3& start, const glm::vec3& end, float width, const glm::vec4& color
) {
	static const Mesh line = geometry::create_line_mesh();
	const glm::vec3 direction = end - start;
	const glm::vec3 normal = glm::normalize(direction);
	const glm::vec3 reference(1.0f, 0.0f, 0.0f);
	float cos_theta = glm::dot(reference, normal);
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
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	set_line_width(width);
	draw_mesh(line);
}

void Renderer::draw_quad(const utility::Transform& transform, const glm::vec4& color) {
	static const Mesh quad = geometry::create_quad_mesh();
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	draw_mesh(quad);
}

void Renderer::draw_quad_outline(
	const utility::Transform& transform, float width, const glm::vec4& color
) {
	static const Mesh quad_outline = geometry::create_quad_outline_mesh();
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	set_line_width(width);
	draw_mesh(quad_outline);
}

void Renderer::draw_circle(const utility::Transform& transform, const glm::vec4& color) {
	static const Mesh circle = geometry::create_circle_mesh(100);
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	draw_mesh(circle);
}

void Renderer::draw_circle_outline(
	const utility::Transform& transform, float width, const glm::vec4& color
) {
	static const Mesh circle_outline = geometry::create_circle_outline_mesh(100);
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	set_line_width(width);
	draw_mesh(circle_outline);
}

void Renderer::draw_cube(const utility::Transform& transform, const glm::vec4& color) {
	static const Mesh cube = geometry::create_cube_mesh();
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	draw_mesh(cube);
}

void Renderer::draw_cube_outline(
	const utility::Transform& transform, float width, const glm::vec4& color
) {
	static const Mesh cube_outline = geometry::create_cube_outline_mesh();
	_shape_shader->set_uniform("u_model", transform.get_model());
	_shape_shader->set_uniform("u_color", color);
	_shape_shader->bind();
	set_line_width(width);
	draw_mesh(cube_outline);
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

void Renderer::set_clear_color(const glm::vec4& color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::set_viewport(const glm::ivec2& position, const glm::ivec2& size) {
	assert(size.x >= 0 && size.y >= 0 && "Viewport size must be positive");
	glViewport(position.x, position.y, size.x, size.y);
	_viewport_position = position;
	_viewport_size = size;
	update_camera_viewport();
}

void Renderer::set_viewport_position(const glm::ivec2& position) {
	set_viewport(position, _viewport_size);
}

void Renderer::set_viewport_size(const glm::ivec2& size) {
	set_viewport(_viewport_position, size);
}

void Renderer::set_point_size(float size) {
	glPointSize(size);
}

void Renderer::set_line_width(float width) {
	glLineWidth(width);
}

void Renderer::set_depth_test(bool enabled) {
	if (enabled) {
		glEnable(GL_DEPTH_TEST);
		_clear_flags.set(ClearFlags::depth);
	} else {
		glDisable(GL_DEPTH_TEST);
		_clear_flags.unset(ClearFlags::depth);
	}
}

void Renderer::set_depth_func(DepthFunc func) {
	glDepthFunc(static_cast<GLenum>(func));
}

void Renderer::set_blend(bool enabled) {
	if (enabled) {
		glEnable(GL_BLEND);
	} else {
		glDisable(GL_BLEND);
	}
}

void Renderer::set_blend_func(BlendFunc src, BlendFunc dst) {
	glBlendFunc(static_cast<GLenum>(src), static_cast<GLenum>(dst));
}

void Renderer::set_blend_equation(BlendEquation eq) {
	glBlendEquation(static_cast<GLenum>(eq));
}

void Renderer::set_stencil(bool enabled) {
	if (enabled) {
		glEnable(GL_STENCIL_TEST);
		_clear_flags.set(ClearFlags::stencil);
	} else {
		glDisable(GL_STENCIL_TEST);
		_clear_flags.unset(ClearFlags::stencil);
	}
}

void Renderer::set_stencil_mask(unsigned int mask) {
	glStencilMask(mask);
}

void Renderer::set_stencil_func(StencilFunc func, int ref, unsigned int mask) {
	glStencilFunc(static_cast<GLenum>(func), ref, mask);
}

void Renderer::set_stencil_op(StencilOp sfail, StencilOp dpfail, StencilOp dppass) {
	glStencilOp(static_cast<GLenum>(sfail), static_cast<GLenum>(dpfail), static_cast<GLenum>(dppass));
}

void Renderer::set_cull_face(bool enabled) {
	if (enabled) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

void Renderer::set_cull_face(CullFace face) {
	glCullFace(static_cast<GLenum>(face));
}

void Renderer::set_front_face(FrontFace face) {
	glFrontFace(static_cast<GLenum>(face));
}

void Renderer::set_polygon_mode(PolygonMode mode) {
	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
}

void Renderer::set_camera(camera::Camera& camera) {
	_camera = &camera;
	update_camera_viewport();
}

auto Renderer::get_viewport_position() -> const glm::ivec2& {
	return _viewport_position;
}

auto Renderer::get_viewport_size() -> const glm::ivec2& {
	return _viewport_size;
}

auto Renderer::get_camera() -> camera::Camera& {
	return *_camera;
}

void Renderer::update_camera_viewport() {
	switch (_camera->get_type()) {
		using enum camera::CameraType;
		case perspective: {
			auto* camera = dynamic_cast<camera::PerspectiveCamera*>(_camera);
			camera->set_aspect(_viewport_size);
			break;
		}
		case orthographic: {
			auto* camera = dynamic_cast<camera::OrthographicCamera*>(_camera);
			camera->set_dimensions(_viewport_size);
			break;
		}
		default:;
	}
}

void Renderer::update_camera_uniform() {
	const glm::mat4& projection = _camera->get_projection();
	const glm::mat4& view = _camera->get_view();
	const glm::mat4& view_projection = _camera->get_view_projection();
	const CameraUniform& uniform_data = _camera_uniform->get_data();
	if (projection != uniform_data.projection) {
		_camera_uniform->set_sub_data(offsetof(CameraUniform, projection), projection);
	}
	if (view != uniform_data.view) {
		_camera_uniform->set_sub_data(offsetof(CameraUniform, view), view);
	}
	if (view_projection != uniform_data.view_projection) {
		_camera_uniform->set_sub_data(offsetof(CameraUniform, view_projection), view_projection);
	}
}

} // namespace void_engine::renderer
