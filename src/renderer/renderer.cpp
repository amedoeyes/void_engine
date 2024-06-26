#include "void_engine/renderer/renderer.hpp"

#include "void_engine/renderer/camera/camera.hpp"
#include "void_engine/utils/logger.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <glad/gl.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>

namespace void_engine::renderer {

bool Renderer::_depth_test = false;
bool Renderer::_blend = false;
bool Renderer::_stencil = false;
glm::vec4 Renderer::_clear_color = glm::vec4(0.f);
glm::vec2 Renderer::_viewport_pos = glm::vec2(0.f);
glm::vec2 Renderer::_viewport_size = glm::vec2(0.f);
camera::Camera* Renderer::_camera = nullptr;

void Renderer::init() {
	if (!gladLoadGL(glfwGetProcAddress)) {
		utils::Logger::error("Failed to initialize GLAD");
		assert(false);
	}

	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_message_callback, nullptr);
		glDebugMessageControl(
			GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true
		);
	}
}

void Renderer::clear() {
	unsigned int mask = GL_COLOR_BUFFER_BIT;
	if (_depth_test) mask |= GL_DEPTH_BUFFER_BIT;
	if (_blend) mask |= GL_BLEND;
	if (_stencil) mask |= GL_STENCIL_BUFFER_BIT;
	glClear(mask);
}

void Renderer::draw_arrays(PrimitiveType type, int first, int count) {
	glDrawArrays(static_cast<unsigned int>(type), first, count);
}

void Renderer::draw_elements(
	PrimitiveType type, unsigned int count, void* indices
) {
	glDrawElements(
		static_cast<unsigned int>(type), static_cast<int>(count),
		GL_UNSIGNED_INT, indices
	);
}

void Renderer::set_clear_color(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
	_clear_color = color;
}

auto Renderer::get_clear_color() -> glm::vec4 {
	return _clear_color;
}

void Renderer::set_viewport(glm::vec2 pos, glm::vec2 size) {
	glViewport(
		static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(size.x), static_cast<int>(size.y)
	);
	_viewport_pos = pos;
	_viewport_size = size;
}

void Renderer::set_viewport_pos(glm::vec2 pos) {
	set_viewport(pos, _viewport_size);
	_viewport_pos = pos;
}

void Renderer::set_viewport_size(glm::vec2 size) {
	set_viewport(_viewport_pos, size);
	_viewport_size = size;
}

void Renderer::set_camera(camera::Camera* camera) {
	_camera = camera;
}

void Renderer::set_depth_test(bool enabled) {
	if (enabled) {
		glEnable(GL_DEPTH_TEST);
		_depth_test = true;
	} else {
		glDisable(GL_DEPTH_TEST);
		_depth_test = false;
	}
}

void Renderer::set_depth_func(DepthFunc func) {
	glDepthFunc(static_cast<unsigned int>(func));
}

void Renderer::set_blend(bool enabled) {
	if (enabled) {
		glEnable(GL_BLEND);
		_blend = true;
	} else {
		glDisable(GL_BLEND);
		_blend = false;
	}
}

void Renderer::set_blend_func(BlendFunc src, BlendFunc dst) {
	glBlendFunc(static_cast<unsigned int>(src), static_cast<unsigned int>(dst));
}

void Renderer::set_blend_equation(BlendEquation eq) {
	glBlendEquation(static_cast<unsigned int>(eq));
}

void Renderer::set_stencil(bool enabled) {
	if (enabled) {
		glEnable(GL_STENCIL_TEST);
		_stencil = true;
	} else {
		glDisable(GL_STENCIL_TEST);
		_stencil = false;
	}
}

void Renderer::set_stencil_mask(unsigned int mask) {
	glStencilMask(mask);
}

void Renderer::set_stencil_func(StencilFunc func, int ref, unsigned int mask) {
	glStencilFunc(static_cast<unsigned int>(func), ref, mask);
}

void Renderer::set_stencil_op(
	StencilOp sfail, StencilOp dpfail, StencilOp dppass
) {
	glStencilOp(
		static_cast<unsigned int>(sfail), static_cast<unsigned int>(dpfail),
		static_cast<unsigned int>(dppass)
	);
}

void Renderer::set_cull_face(bool enabled) {
	if (enabled) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

void Renderer::set_cull_face(CullFace face) {
	glCullFace(static_cast<unsigned int>(face));
}

void Renderer::set_front_face(FrontFace face) {
	glFrontFace(static_cast<unsigned int>(face));
}

void Renderer::set_polygon_mode(PolygonMode mode) {
	glPolygonMode(GL_FRONT_AND_BACK, static_cast<unsigned int>(mode));
}

auto Renderer::get_viewport_pos() -> glm::vec2 {
	return _viewport_pos;
}

auto Renderer::get_viewport_size() -> glm::vec2 {
	return _viewport_size;
}

auto Renderer::get_camera() -> camera::Camera* {
	return _camera;
}

void Renderer::
	debug_message_callback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int, const char* message, const void*) {
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::string source_str;
	switch (source) {
		case GL_DEBUG_SOURCE_API: source_str = "API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: source_str = "Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			source_str = "Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY: source_str = "Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION: source_str = "Application"; break;
		case GL_DEBUG_SOURCE_OTHER: source_str = "Other"; break;
		default:;
	}

	std::string type_str;
	switch (type) {
		case GL_DEBUG_TYPE_ERROR: type_str = "Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			type_str = "Deprecated Behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			type_str = "Undefined Behaviour";
			break;
		case GL_DEBUG_TYPE_PORTABILITY: type_str = "Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE: type_str = "Performance"; break;
		case GL_DEBUG_TYPE_MARKER: type_str = "Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP: type_str = "Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP: type_str = "Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER: type_str = "Other"; break;
		default:;
	}

	std::string severity_str;
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH: severity_str = "high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM: severity_str = "medium"; break;
		case GL_DEBUG_SEVERITY_LOW: severity_str = "low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			severity_str = "notification";
			break;
		default:;
	}

	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
		utils::Logger::info(
			"OpenGL: [{}] [{}] [{}] [{}] {}", source_str, type_str,
			severity_str, id, message
		);
	} else {
		utils::Logger::error(
			"OpenGL: [{}] [{}] [{}] [{}] {}", source_str, type_str,
			severity_str, id, message
		);
	}
}

} // namespace void_engine::renderer
