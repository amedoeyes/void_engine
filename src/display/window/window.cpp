#include "void_engine/display/window/window.hpp"

#include "void_engine/display/monitor/monitor.hpp"
#include "void_engine/display/window/window_event_handler.hpp"
#include "void_engine/display/window/window_input_handler.hpp"
#include "void_engine/utility/get_exec_path.hpp"
#include "void_engine/resource/image/image.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <cstddef>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace void_engine::display::window {

Window::Window(std::string_view title, const glm::ivec2& size) {
	_window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
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

auto Window::event_handler() -> WindowEventHandler& {
	return *_event_handler;
}

auto Window::input_handler() -> WindowInputHandler& {
	return *_input_handler;
}

void Window::close() const {
	glfwSetWindowShouldClose(_window, 1);
}

void Window::focus() const {
	glfwFocusWindow(_window);
}

void Window::make_context_current() const {
	glfwMakeContextCurrent(_window);
}

void Window::swap_buffers() const {
	glfwSwapBuffers(_window);
}

void Window::update() {
	_input_handler->update();
	_event_handler->poll();
	swap_buffers();
}

void Window::show() const {
	glfwShowWindow(_window);
}

void Window::hide() const {
	glfwHideWindow(_window);
}

void Window::iconify() const {
	glfwIconifyWindow(_window);
}

void Window::maximize() const {
	glfwMaximizeWindow(_window);
}

void Window::restore() const {
	glfwRestoreWindow(_window);
}

void Window::fullscreen() const {
	auto* const monitor = glfwGetPrimaryMonitor();
	const auto* const mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void Window::fullscreen(const monitor::Monitor& monitor) const {
	const auto* const mode = glfwGetVideoMode(monitor._monitor);
	glfwSetWindowMonitor(
		_window, monitor._monitor, 0, 0, mode->width, mode->height, mode->refreshRate
	);
}

void Window::windowed(const glm::ivec2& position, const glm::ivec2& size) const {
	glfwSetWindowMonitor(_window, nullptr, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);
}

void Window::set_aspect_ratio(int numerator, int denominator) {
	glfwSetWindowAspectRatio(_window, numerator, denominator);
}

void Window::set_auto_iconify(bool value) {
	glfwSetWindowAttrib(_window, GLFW_AUTO_ICONIFY, static_cast<int>(value));
}

void Window::set_decorated(bool value) {
	glfwSetWindowAttrib(_window, GLFW_DECORATED, static_cast<int>(value));
}

void Window::set_floating(bool value) {
	glfwSetWindowAttrib(_window, GLFW_FLOATING, static_cast<int>(value));
}

void Window::set_focus_on_show(bool value) {
	glfwSetWindowAttrib(_window, GLFW_FOCUS_ON_SHOW, static_cast<int>(value));
}

void Window::set_opacity(float opacity) {
	glfwSetWindowOpacity(_window, opacity);
}

void Window::set_position(const glm::ivec2& position) {
	glfwSetWindowPos(_window, position.x, position.y);
}

void Window::set_resizable(bool value) {
	glfwSetWindowAttrib(_window, GLFW_RESIZABLE, static_cast<int>(value));
}

void Window::set_size(const glm::ivec2& size) {
	glfwSetWindowSize(_window, size.x, size.y);
}

void Window::set_size_limits(const glm::ivec2& min, const glm::ivec2& max) {
	glfwSetWindowSizeLimits(_window, min.x, min.y, max.x, max.y);
}

void Window::set_title(std::string_view title) {
	glfwSetWindowTitle(_window, title.data());
}

void Window::set_icon(std::string_view path) {
	glfwSetWindowIcon(_window, 0, nullptr);
	const resource::image::Image image(utility::get_exec_path().parent_path() / path, true);
	const glm::uvec2 size = image.get_size();
	const GLFWimage glfw_image = {
		.width = static_cast<int>(size.x),
		.height = static_cast<int>(size.y),
		.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
	};
	glfwSetWindowIcon(_window, 1, &glfw_image);
}

void Window::set_icons(std::vector<std::string_view> paths) {
	const std::vector<resource::image::Image*> images(paths.size());
	std::vector<GLFWimage> glfw_images(paths.size());
	for (size_t i = 0; i < paths.size(); ++i) {
		const resource::image::Image image(utility::get_exec_path().parent_path() / paths[i], true);
		const glm::uvec2 size = image.get_size();
		glfw_images[i] = {
			.width = static_cast<int>(size.x),
			.height = static_cast<int>(size.y),
			.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
		};
	}
	glfwSetWindowIcon(_window, static_cast<int>(glfw_images.size()), glfw_images.data());
}

auto Window::get_content_scale() const -> glm::vec2 {
	float x = 0.0f;
	float y = 0.0f;
	glfwGetWindowContentScale(_window, &x, &y);
	return {x, y};
}

auto Window::get_frame_size() const -> std::tuple<int, int, int, int> {
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	glfwGetWindowFrameSize(_window, &left, &top, &right, &bottom);
	return {left, top, right, bottom};
}

auto Window::get_framebuffer_position() const -> glm::ivec2 {
	int x = 0;
	int y = 0;
	glfwGetWindowPos(_window, &x, &y);
	return {x, y};
}

auto Window::get_framebuffer_size() const -> glm::ivec2 {
	int width = 0;
	int height = 0;
	glfwGetFramebufferSize(_window, &width, &height);
	return {width, height};
}

auto Window::get_opacity() const -> float {
	return glfwGetWindowOpacity(_window);
}

auto Window::get_position() const -> glm::ivec2 {
	int x = 0;
	int y = 0;
	glfwGetWindowPos(_window, &x, &y);
	return {x, y};
}

auto Window::get_size() const -> glm::ivec2 {
	int width = 0;
	int height = 0;
	glfwGetWindowSize(_window, &width, &height);
	return {width, height};
}

auto Window::get_title() const -> std::string {
	return glfwGetWindowTitle(_window);
}

auto Window::is_auto_iconified() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_ICONIFIED) != 0;
}

auto Window::is_close_requested() const -> bool {
	return glfwWindowShouldClose(_window) != 0;
}

auto Window::is_decorated() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_DECORATED) != 0;
}

auto Window::is_focused() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_FOCUSED) != 0;
}

auto Window::is_floating() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_FLOATING) != 0;
}

auto Window::is_focus_on_show() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_FOCUS_ON_SHOW) != 0;
}

auto Window::is_maximized() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) != 0;
}

auto Window::is_mouse_passthrough() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_MOUSE_PASSTHROUGH) != 0;
}

auto Window::is_resizable() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_RESIZABLE) != 0;
}

auto Window::is_scale_framebuffer() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_SCALE_TO_MONITOR) != 0;
}

auto Window::is_scale_to_monitor() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_SCALE_TO_MONITOR) != 0;
}

auto Window::is_transparent_framebuffer() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_TRANSPARENT_FRAMEBUFFER) != 0;
}

auto Window::is_visible() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_VISIBLE) != 0;
}

} // namespace void_engine::display::window
