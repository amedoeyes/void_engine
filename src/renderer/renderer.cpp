#include "void_engine/renderer/renderer.hpp"

#include "GLFW/glfw3.h"
#include "void_engine/logger.hpp"

#include <cassert>

namespace void_engine::renderer {

bool Renderer::_depth_test = false;
bool Renderer::_blend = false;
bool Renderer::_stencil = false;

void Renderer::init() {
	if (!gladLoadGL(glfwGetProcAddress)) {
		Logger::error("Failed to initialize GLAD");
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
	PrimitiveType type, int count, DataType indices_type, void* indices
) {
	glDrawElements(
		static_cast<unsigned int>(type), count,
		static_cast<unsigned int>(indices_type), indices
	);
}

void Renderer::set_clear_color(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::set_viewport(glm::vec<2, int> pos, glm::vec<2, int> size) {
	glViewport(pos.x, pos.y, size.x, size.y);
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

void Renderer::debug_message_callback(
	unsigned int source, unsigned int type, unsigned int id, // NOLINT
	unsigned int severity, int, const char* message, const void* 
) {
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
	}

	std::string severity_str;
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH: severity_str = "high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM: severity_str = "medium"; break;
		case GL_DEBUG_SEVERITY_LOW: severity_str = "low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			severity_str = "notification";
			break;
	}

	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
		Logger::info(
			"OpenGL: [{}] [{}] [{}] [{}] {}", source_str, type_str,
			severity_str, id, message
		);
	} else {
		Logger::error(
			"OpenGL: [{}] [{}] [{}] [{}] {}", source_str, type_str,
			severity_str, id, message
		);
	}
}

} // namespace void_engine::renderer
