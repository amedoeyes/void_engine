#include "void_engine/graphics/renderer/renderer.hpp"

#include "void_engine/graphics/buffer/enums.hpp"
#include "void_engine/graphics/buffer/uniform_buffer.hpp"
#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/graphics/camera/enums.hpp"
#include "void_engine/graphics/camera/orthographic_camera.hpp"
#include "void_engine/graphics/camera/perspective_camera.hpp"
#include "void_engine/graphics/geometry/circle.hpp"
#include "void_engine/graphics/geometry/cube.hpp"
#include "void_engine/graphics/geometry/line.hpp"
#include "void_engine/graphics/geometry/point.hpp"
#include "void_engine/graphics/geometry/quad.hpp"
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
#include <tuple>
#include <utility>

namespace void_engine::graphics::renderer {

struct CameraUniform {
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 view_projection;
};

struct Viewport {
	glm::ivec2 position = {0, 0};
	glm::ivec2 size = {0, 0};
};

struct Context {
	Viewport viewport;
	utility::BitMask<ClearFlags> clear_flags;
	resource::ResourceManager resource_manager;
	buffer::UniformBuffer<CameraUniform> camera_uniform;
	camera::Camera* default_camera = nullptr;
	camera::Camera* camera = nullptr;
	glm::mat4 screen_projection = glm::mat4(1.0f);
	resource::font::Text text;
};

namespace {

auto get_context() -> Context& {
	static Context context;
	return context;
}

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

void update_camera_viewport() {
	static const Context& context = get_context();
	switch (context.camera->get_type()) {
		using enum camera::Type;
		case perspective: {
			auto* camera = dynamic_cast<camera::PerspectiveCamera*>(context.camera);
			camera->set_aspect(context.viewport.size);
			break;
		}
		case orthographic: {
			auto* camera = dynamic_cast<camera::OrthographicCamera*>(context.camera);
			camera->set_dimensions(context.viewport.size);
			break;
		}
		default: std::unreachable();
	}
}

void update_camera_uniform() {
	static Context& context = get_context();
	const glm::mat4& projection = context.camera->get_projection();
	const glm::mat4& view = context.camera->get_view();
	const glm::mat4& view_projection = context.camera->get_view_projection();
	const CameraUniform& uniform_data = context.camera_uniform.get_data();
	if (projection != uniform_data.projection) {
		context.camera_uniform.set_sub_data(offsetof(CameraUniform, projection), projection);
	}
	if (view != uniform_data.view) {
		context.camera_uniform.set_sub_data(offsetof(CameraUniform, view), view);
	}
	if (view_projection != uniform_data.view_projection) {
		context.camera_uniform.set_sub_data(offsetof(CameraUniform, view_projection), view_projection);
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

void init() {
	if (gladLoadGL() == 0) {
		assert(false && "Failed to initialize GLAD");
	}

	int flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if ((static_cast<unsigned int>(flags) & GL_CONTEXT_FLAG_DEBUG_BIT) != 0) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_message_callback, nullptr);
	}

	Context& context = get_context();

	context.clear_flags.set(ClearFlags::color);

	context.default_camera = new camera::PerspectiveCamera();
	context.camera = context.default_camera;

	context.camera_uniform.bind_range(0);
	context.camera_uniform.allocate(sizeof(CameraUniform), buffer::Usage::dynamic_draw);

	resource::shader::Shader& shape_shader = context.resource_manager.shaders().create("shape");
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

	resource::shader::Shader& font_shader = context.resource_manager.shaders().create("font");
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

	resource::shader::Shader& font_screen_shader =
		context.resource_manager.shaders().create("font_screen");
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

	const resource::font::Font& font = context.resource_manager.fonts().create(
		"liberation", std::as_bytes(std::span(liberation_font))
	);

	context.text.set_font(font);
}

void update() {
	update_camera_uniform();
	clear();
}

void terminate() {
	static const Context& context = get_context();
	delete context.default_camera;
}

void clear() {
	static const Context& context = get_context();
	glClear(context.clear_flags.get());
}

void draw_mesh(const Mesh& mesh) {
	mesh.bind();
	draw_elements(mesh.get_primitive_type(), mesh.get_count(), nullptr);
}

void draw_mesh_instanced(const Mesh& mesh, unsigned int instances) {
	mesh.bind();
	draw_elements_instanced(mesh.get_primitive_type(), mesh.get_count(), nullptr, instances);
}

void draw_point(const glm::vec3& position, float size, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh point = geometry::create_point_mesh();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, glm::translate(glm::mat4(1.0f), position));
	shader.set_uniform(1, color);
	shader.bind();
	set_point_size(size);
	draw_mesh(point);
}

void draw_line(const glm::vec3& start, const glm::vec3& end, float width, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh line = geometry::create_line_mesh();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
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
	draw_mesh(line);
}

void draw_quad(const utility::Transform& transform, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh quad = geometry::create_quad_mesh();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	draw_mesh(quad);
}

void draw_quad_outline(const utility::Transform& transform, float width, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh quad_outline = geometry::create_quad_outline_mesh();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(quad_outline);
}

void draw_circle(const utility::Transform& transform, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh circle = geometry::create_circle_mesh(100);
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	draw_mesh(circle);
}

void draw_circle_outline(const utility::Transform& transform, float width, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh circle_outline = geometry::create_circle_outline_mesh(100);
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(circle_outline);
}

void draw_cube(const utility::Transform& transform, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh cube = geometry::create_cube_mesh();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	draw_mesh(cube);
}

void draw_cube_outline(const utility::Transform& transform, float width, const glm::vec4& color) {
	static Context& context = get_context();
	static const Mesh cube_outline = geometry::create_cube_outline_mesh();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("shape");
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, color);
	shader.bind();
	set_line_width(width);
	draw_mesh(cube_outline);
}

void draw_elements(PrimitiveType type, unsigned int count, void* indices) {
	glDrawElements(static_cast<GLenum>(type), static_cast<GLsizei>(count), GL_UNSIGNED_INT, indices);
}

void draw_elements_instanced(
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

void draw_text(
	const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
) {
	static Context& context = get_context();
	static const resource::shader::Shader& shader = context.resource_manager.shaders().get("font");
	const bool prev_blend = is_blend_enabled();
	auto [prev_src, prev_dst] = get_blend_func();
	set_blend(true);
	set_blend_func(BlendFunc::src_alpha, BlendFunc::one_minus_src_alpha);
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(2, color);
	shader.bind();
	text.get_font().get_texture().bind_unit(0);
	draw_mesh(text.get_mesh());
	set_blend(prev_blend);
	set_blend_func(prev_src, prev_dst);
}

void draw_text(std::string_view text, const utility::Transform& transform, const glm::vec4& color) {
	static Context& context = get_context();
	context.text.set_data(text);
	draw_text(context.text, transform, color);
}

void draw_text_screen(
	const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
) {
	static Context& context = get_context();
	static const resource::shader::Shader& shader =
		context.resource_manager.shaders().get("font_screen");
	const bool prev_blend = is_blend_enabled();
	auto [prev_src, prev_dst] = get_blend_func();
	set_blend(true);
	set_blend_func(BlendFunc::src_alpha, BlendFunc::one_minus_src_alpha);
	text.get_font().get_texture().bind_unit(0);
	shader.set_uniform(0, transform.get_model());
	shader.set_uniform(1, context.screen_projection);
	shader.set_uniform(2, color);
	shader.bind();
	draw_mesh(text.get_mesh());
	set_blend(prev_blend);
	set_blend_func(prev_src, prev_dst);
}

void draw_text_screen(
	std::string_view text, const utility::Transform& transform, const glm::vec4& color
) {
	static Context& context = get_context();
	context.text.set_data(text);
	draw_text_screen(context.text, transform, color);
}

void set_clear_color(const glm::vec4& color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void set_viewport(const glm::ivec2& position, const glm::ivec2& size) {
	assert(size.x >= 0 && size.y >= 0 && "Viewport size must be positive");
	static Context& context = get_context();
	glViewport(position.x, position.y, size.x, size.y);
	context.viewport.position = position;
	context.viewport.size = size;
	context.screen_projection =
		glm::ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y));
	update_camera_viewport();
}

void set_viewport_position(const glm::ivec2& position) {
	static const Context& context = get_context();
	set_viewport(position, context.viewport.size);
}

void set_viewport_size(const glm::ivec2& size) {
	static const Context& context = get_context();
	set_viewport(context.viewport.position, size);
}

void set_point_size(float size) {
	glPointSize(size);
}

void set_line_width(float width) {
	glLineWidth(width);
}

void set_depth_test(bool enabled) {
	static Context& context = get_context();
	if (enabled) {
		glEnable(GL_DEPTH_TEST);
		context.clear_flags.set(ClearFlags::depth);
	} else {
		glDisable(GL_DEPTH_TEST);
		context.clear_flags.unset(ClearFlags::depth);
	}
}

void set_depth_func(DepthFunc func) {
	glDepthFunc(static_cast<GLenum>(func));
}

void set_blend(bool enabled) {
	if (enabled) {
		glEnable(GL_BLEND);
	} else {
		glDisable(GL_BLEND);
	}
}

void set_blend_func(BlendFunc src, BlendFunc dst) {
	glBlendFunc(static_cast<GLenum>(src), static_cast<GLenum>(dst));
}

void set_blend_equation(BlendEquation eq) {
	glBlendEquation(static_cast<GLenum>(eq));
}

void set_stencil(bool enabled) {
	static Context& context = get_context();
	if (enabled) {
		glEnable(GL_STENCIL_TEST);
		context.clear_flags.set(ClearFlags::stencil);
	} else {
		glDisable(GL_STENCIL_TEST);
		context.clear_flags.unset(ClearFlags::stencil);
	}
}

void set_stencil_mask(unsigned int mask) {
	glStencilMask(mask);
}

void set_stencil_func(StencilFunc func, int ref, unsigned int mask) {
	glStencilFunc(static_cast<GLenum>(func), ref, mask);
}

void set_stencil_op(StencilOp sfail, StencilOp dpfail, StencilOp dppass) {
	glStencilOp(static_cast<GLenum>(sfail), static_cast<GLenum>(dpfail), static_cast<GLenum>(dppass));
}

void set_cull_face(bool enabled) {
	if (enabled) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

void set_cull_face(CullFace face) {
	glCullFace(static_cast<GLenum>(face));
}

void set_front_face(FrontFace face) {
	glFrontFace(static_cast<GLenum>(face));
}

void set_polygon_mode(PolygonMode mode) {
	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
}

void set_camera(camera::Camera& camera) {
	static Context& context = get_context();
	context.camera = &camera;
	update_camera_viewport();
}

auto get_viewport_position() -> const glm::ivec2& {
	static const Context& context = get_context();
	return context.viewport.position;
}

auto get_viewport_size() -> const glm::ivec2& {
	static const Context& context = get_context();
	return context.viewport.size;
}

auto is_blend_enabled() -> bool {
	return glIsEnabled(GL_BLEND) == GL_TRUE;
}

auto get_blend_func() -> std::pair<BlendFunc, BlendFunc> {
	int src = 0;
	int dst = 0;
	glGetIntegerv(GL_BLEND_SRC, &src);
	glGetIntegerv(GL_BLEND_DST, &dst);
	return {static_cast<BlendFunc>(src), static_cast<BlendFunc>(dst)};
}

auto get_blend_equation() -> BlendEquation {
	int eq = 0;
	glGetIntegerv(GL_BLEND_EQUATION, &eq);
	return static_cast<BlendEquation>(eq);
}

auto is_stencil_enabled() -> bool {
	return glIsEnabled(GL_STENCIL_TEST) == GL_TRUE;
}

auto get_stencil_mask() -> unsigned int {
	int mask = 0;
	glGetIntegerv(GL_STENCIL_WRITEMASK, &mask);
	return static_cast<unsigned int>(mask);
}

auto get_stencil_func() -> std::tuple<StencilFunc, int, unsigned int> {
	int func = 0;
	int ref = 0;
	int mask = 0;
	glGetIntegerv(GL_STENCIL_FUNC, &func);
	glGetIntegerv(GL_STENCIL_REF, &ref);
	glGetIntegerv(GL_STENCIL_VALUE_MASK, &mask);
	return {static_cast<StencilFunc>(func), ref, static_cast<unsigned int>(mask)};
}

auto get_stencil_op() -> std::tuple<StencilOp, StencilOp, StencilOp> {
	int sfail = 0;
	int dpfail = 0;
	int dppass = 0;
	glGetIntegerv(GL_STENCIL_FAIL, &sfail);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &dpfail);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &dppass);
	return {
		static_cast<StencilOp>(sfail), static_cast<StencilOp>(dpfail), static_cast<StencilOp>(dppass)
	};
}

auto is_cull_face_enabled() -> bool {
	return glIsEnabled(GL_CULL_FACE) == GL_TRUE;
}

auto get_cull_face() -> CullFace {
	int face = 0;
	glGetIntegerv(GL_CULL_FACE, &face);
	return static_cast<CullFace>(face);
}

auto get_front_face() -> FrontFace {
	int face = 0;
	glGetIntegerv(GL_FRONT_FACE, &face);
	return static_cast<FrontFace>(face);
}

auto get_polygon_mode() -> PolygonMode {
	int mode = 0;
	glGetIntegerv(GL_POLYGON_MODE, &mode);
	return static_cast<PolygonMode>(mode);
}

auto get_camera() -> camera::Camera& {
	static const Context& context = get_context();
	return *context.camera;
}

} // namespace void_engine::graphics::renderer
