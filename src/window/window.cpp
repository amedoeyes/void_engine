#include "void_engine/window/window.hpp"

#include "void_engine/logger.hpp"

namespace void_engine::window {

Window::Window(const char* title, const int& width, const int& height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (_window == nullptr) Logger::error("Failed to create window");

	glfwMakeContextCurrent(_window);

	glfwSetErrorCallback([]([[maybe_unused]] int, const char* description) {
		Logger::error("GLFW Error: {}", description);
	});

	_input_handler = new InputHandler(_window);
}

Window::~Window() {
	delete _input_handler;
	glfwDestroyWindow(_window);
}

GLFWwindow* Window::get_window() const {
	return _window;
}

void Window::make_context_current() const {
	glfwMakeContextCurrent(_window);
}

void Window::swap_buffers() const {
	glfwSwapBuffers(_window);
}

bool Window::should_close() const {
	return glfwWindowShouldClose(_window);
}

void Window::close() const {
	glfwSetWindowShouldClose(_window, true);
}

InputHandler* Window::get_input_handler() const {
	return _input_handler;
}

float Window::get_time() const {
	return glfwGetTime();
}

}  // namespace void_engine::window
