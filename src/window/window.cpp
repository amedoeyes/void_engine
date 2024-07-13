#include "void_engine/window/window.hpp"

#include "void_engine/window/window_event_handler.hpp"
#include "void_engine/window/window_input_handler.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/ext/vector_float2.hpp>
#include <string_view>

namespace void_engine::window {

Window::Window(std::string_view title, const glm::vec2& size) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#endif

	_window = glfwCreateWindow(
		static_cast<int>(size.x), static_cast<int>(size.y), title.data(), nullptr, nullptr
	);
	assert(_window != nullptr && "Failed to create window");

	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, this);

	_event_handler = new WindowEventHandler(*this);
	_input_handler = new WindowInputHandler(*this);
}

Window::~Window() {
	delete _input_handler;
	delete _event_handler;
	glfwDestroyWindow(_window);
}

void Window::make_context_current() const {
	glfwMakeContextCurrent(_window);
}

void Window::swap_buffers() const {
	glfwSwapBuffers(_window);
}

void Window::close() const {
	glfwSetWindowShouldClose(_window, 1);
}

void Window::update() {
	_input_handler->update();
	_event_handler->poll();
	swap_buffers();
}

auto Window::event_handler() -> WindowEventHandler& {
	return *_event_handler;
}

auto Window::input_handler() -> WindowInputHandler& {
	return *_input_handler;
}

auto Window::should_close() const -> bool {
	return glfwWindowShouldClose(_window) != 0;
}

auto Window::get_size() const -> glm::vec2 {
	int width = 0;
	int height = 0;
	glfwGetWindowSize(_window, &width, &height);
	return {width, height};
}

} // namespace void_engine::window
