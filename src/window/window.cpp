#include "void_engine/window/window.hpp"

#include "void_engine/input/input_handler.hpp"
#include "void_engine/utils/logger.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <string_view>

namespace void_engine::window {

Window::Window(const std::string_view title, int width, int height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	_window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
	if (_window == nullptr) utils::Logger::error("Failed to create window");

	glfwMakeContextCurrent(_window);

	glfwSetErrorCallback([](int, const char* description) {
		utils::Logger::error("GLFW Error: {}", description);
	});

	_input_handler = new input::InputHandler(_window);

	glfwSetWindowUserPointer(_window, this);
}

Window::~Window() {
	delete _input_handler;
	glfwDestroyWindow(_window);
}

auto Window::get_window() const -> GLFWwindow* {
	return _window;
}

void Window::make_context_current() const {
	glfwMakeContextCurrent(_window);
}

void Window::swap_buffers() const {
	glfwSwapBuffers(_window);
}

auto Window::should_close() const -> bool {
	return glfwWindowShouldClose(_window);
}

void Window::close() const {
	glfwSetWindowShouldClose(_window, true);
}

auto Window::get_input_handler() const -> input::InputHandler* {
	return _input_handler;
}

auto Window::get_time() const -> float {
	return static_cast<float>(glfwGetTime());
}

auto Window::get_delta_time() const -> float {
	static float last_frame_time = 0.0f;
	auto current_time = static_cast<float>(glfwGetTime());
	const float delta_time = current_time - last_frame_time;
	last_frame_time = current_time;
	return delta_time;
}

auto Window::get_size() const -> glm::vec2 {
	int width, height;
	glfwGetWindowSize(_window, &width, &height);
	return {width, height};
}

} // namespace void_engine::window
