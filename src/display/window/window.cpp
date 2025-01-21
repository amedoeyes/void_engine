#include "void_engine/display/window/window.hpp"

#include "void_engine/display/monitor/video_mode.hpp"
#include "void_engine/display/window/hints.hpp"
#include "void_engine/display/window/window_event_handler.hpp"
#include "void_engine/display/window/window_input_handler.hpp"
#include "void_engine/resource/image/image.hpp"

#include <GLFW/glfw3.h>
#include <bit>
#include <cassert>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <span>
#include <string_view>
#include <tuple>
#include <vector>

import void_engine.display.monitor;

namespace void_engine::display::window {

Window::Window(
	std::string_view title, const glm::ivec2& size, const monitor::Monitor& monitor,
	const Window& share, const Hints& hints
) :
	Window(title, size, monitor.raw(), share._window, hints) {
}

Window::Window(
	std::string_view title, const glm::ivec2& size, const monitor::Monitor& monitor,
	const Hints& hints
) :
	Window(title, size, monitor.raw(), nullptr, hints) {
}

Window::Window(
	std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints
) :
	Window(title, size, nullptr, share._window, hints) {
}

Window::Window(std::string_view title, const glm::ivec2& size, const Hints& hints) :
	Window(title, size, nullptr, nullptr, hints) {
}

Window::Window(
	std::string_view title, const glm::ivec2& size, GLFWmonitor* monitor, GLFWwindow* share,
	const Hints& hints
) {
	apply_hints(hints);
	_window = glfwCreateWindow(size.x, size.y, std::string(title).c_str(), monitor, share);
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

void Window::update() {
	_input_handler->update();
	_event_handler->poll();
}

void Window::swap_buffers() const {
	glfwSwapBuffers(_window);
}

void Window::bind() const {
	glfwMakeContextCurrent(_window);
}

void Window::unbind() {
	glfwMakeContextCurrent(nullptr);
}

void Window::close() const {
	glfwSetWindowShouldClose(_window, 1);
}

void Window::focus() const {
	glfwFocusWindow(_window);
}

void Window::hide() const {
	glfwHideWindow(_window);
}

void Window::show() const {
	glfwShowWindow(_window);
}

void Window::maximize() const {
	glfwMaximizeWindow(_window);
}

void Window::minimize() const {
	glfwIconifyWindow(_window);
}

void Window::restore() const {
	glfwRestoreWindow(_window);
}

void Window::fullscreen() const {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void Window::fullscreen(const monitor::Monitor& monitor) const {
	const monitor::VideoMode& mode = monitor.get_video_mode();
	glfwSetWindowMonitor(_window, monitor.raw(), 0, 0, mode.size.x, mode.size.y, mode.refresh_rate);
}

void Window::fullscreen(const monitor::Monitor& monitor, const monitor::VideoMode& video_mode)
	const {
	glfwSetWindowMonitor(
		_window, monitor.raw(), 0, 0, video_mode.size.x, video_mode.size.y, video_mode.refresh_rate
	);
}

void Window::windowed(const glm::ivec2& position, const glm::ivec2& size) const {
	glfwSetWindowMonitor(_window, nullptr, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);
}

void Window::set_aspect_ratio(const glm::ivec2& ratio) {
	glfwSetWindowAspectRatio(_window, ratio.x, ratio.y);
}

void Window::set_auto_minimize(bool enabled) {
	glfwSetWindowAttrib(_window, GLFW_AUTO_ICONIFY, static_cast<int>(enabled));
}

void Window::set_decoration(bool enabled) {
	glfwSetWindowAttrib(_window, GLFW_DECORATED, static_cast<int>(enabled));
}

void Window::set_floating(bool enabled) {
	glfwSetWindowAttrib(_window, GLFW_FLOATING, static_cast<int>(enabled));
}

void Window::set_focus_on_show(bool enabled) {
	glfwSetWindowAttrib(_window, GLFW_FOCUS_ON_SHOW, static_cast<int>(enabled));
}

void Window::set_icon(const std::filesystem::path& path) {
	glfwSetWindowIcon(_window, 0, nullptr);
	const resource::image::Image image(path, true);
	const glm::ivec2& size = image.get_size();
	const GLFWimage glfw_image = {
		.width = size.x,
		.height = size.y,
		.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
	};
	glfwSetWindowIcon(_window, 1, &glfw_image);
}

void Window::set_icons(std::span<std::filesystem::path> paths) {
	std::vector<GLFWimage> images;
	images.reserve(paths.size());
	for (const auto& path : paths) {
		const resource::image::Image image(path, true);
		const glm::ivec2& size = image.get_size();
		images.push_back({
			.width = size.x,
			.height = size.y,
			.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
		});
	}
	glfwSetWindowIcon(_window, static_cast<int>(images.size()), images.data());
}

void Window::set_opacity(float alpha) {
	glfwSetWindowOpacity(_window, alpha);
}

void Window::set_position(const glm::ivec2& position) {
	glfwSetWindowPos(_window, position.x, position.y);
}

void Window::set_resizable(bool enabled) {
	glfwSetWindowAttrib(_window, GLFW_RESIZABLE, static_cast<int>(enabled));
}

void Window::set_size(const glm::ivec2& size) {
	glfwSetWindowSize(_window, size.x, size.y);
}

void Window::set_size_constraints(const glm::ivec2& min, const glm::ivec2& max) {
	glfwSetWindowSizeLimits(_window, min.x, min.y, max.x, max.y);
}

void Window::set_title(std::string_view title) {
	glfwSetWindowTitle(_window, std::string(title).c_str());
}

void Window::set_vsync(bool enabled) {
	set_swap_interval(enabled ? 1 : 0);
}

void Window::set_swap_interval(int interval) {
	glfwSwapInterval(interval);
}

auto Window::get_event_handler() -> WindowEventHandler& {
	return *_event_handler;
}

auto Window::get_input_handler() -> WindowInputHandler& {
	return *_input_handler;
}

auto Window::get_content_scale() const -> glm::vec2 {
	float x = 0.0f;
	float y = 0.0f;
	glfwGetWindowContentScale(_window, &x, &y);
	return {x, y};
}

auto Window::get_frame_size() const -> std::tuple<glm::ivec2, glm::ivec2> {
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	glfwGetWindowFrameSize(_window, &left, &top, &right, &bottom);
	return {{left, top}, {right, bottom}};
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

auto Window::get_title() const -> std::string_view {
	return glfwGetWindowTitle(_window);
}

auto Window::has_focus_on_show() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_FOCUS_ON_SHOW) != 0;
}

auto Window::has_mouse_passthrough() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_MOUSE_PASSTHROUGH) != 0;
}

auto Window::has_transparent_framebuffer() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_TRANSPARENT_FRAMEBUFFER) != 0;
}

auto Window::is_decorated() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_DECORATED) != 0;
}

auto Window::is_floating() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_FLOATING) != 0;
}

auto Window::is_focused() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_FOCUSED) != 0;
}

auto Window::is_maximized() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) != 0;
}

auto Window::is_minimized() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_ICONIFIED) != 0;
}

auto Window::is_resizable() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_RESIZABLE) != 0;
}

auto Window::is_visible() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_VISIBLE) != 0;
}

auto Window::scales_framebuffer_to_monitor() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_SCALE_FRAMEBUFFER) != 0;
}

auto Window::scales_to_monitor() const -> bool {
	return glfwGetWindowAttrib(_window, GLFW_SCALE_TO_MONITOR) != 0;
}

auto Window::should_close() const -> bool {
	return glfwWindowShouldClose(_window) != 0;
}

void Window::apply_hints(const Hints& hints) {
	glfwWindowHint(GLFW_RESIZABLE, static_cast<int>(hints.window.resizable));
	glfwWindowHint(GLFW_VISIBLE, static_cast<int>(hints.window.visible));
	glfwWindowHint(GLFW_DECORATED, static_cast<int>(hints.window.decorated));
	glfwWindowHint(GLFW_FOCUSED, static_cast<int>(hints.window.focused));
	glfwWindowHint(GLFW_AUTO_ICONIFY, static_cast<int>(hints.window.auto_minimize));
	glfwWindowHint(GLFW_FLOATING, static_cast<int>(hints.window.floating));
	glfwWindowHint(GLFW_MAXIMIZED, static_cast<int>(hints.window.maximized));
	glfwWindowHint(GLFW_CENTER_CURSOR, static_cast<int>(hints.window.center_cursor));
	glfwWindowHint(
		GLFW_TRANSPARENT_FRAMEBUFFER, static_cast<int>(hints.window.transparent_framebuffer)
	);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, static_cast<int>(hints.window.focus_on_show));
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, static_cast<int>(hints.window.scale_to_monitor));
	glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, static_cast<int>(hints.window.scale_framebuffer));
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, static_cast<int>(hints.window.mouse_passthrough));
	glfwWindowHint(GLFW_POSITION_X, hints.window.position.x);
	glfwWindowHint(GLFW_POSITION_Y, hints.window.position.y);

	glfwWindowHint(GLFW_RED_BITS, hints.framebuffer.color_bits.r);
	glfwWindowHint(GLFW_GREEN_BITS, hints.framebuffer.color_bits.g);
	glfwWindowHint(GLFW_BLUE_BITS, hints.framebuffer.color_bits.b);
	glfwWindowHint(GLFW_ALPHA_BITS, hints.framebuffer.color_bits.a);
	glfwWindowHint(GLFW_DEPTH_BITS, hints.framebuffer.depth_bits);
	glfwWindowHint(GLFW_STENCIL_BITS, hints.framebuffer.stencil_bits);
	glfwWindowHint(GLFW_ACCUM_RED_BITS, hints.framebuffer.accumulation_color_bits.r);
	glfwWindowHint(GLFW_ACCUM_GREEN_BITS, hints.framebuffer.accumulation_color_bits.g);
	glfwWindowHint(GLFW_ACCUM_BLUE_BITS, hints.framebuffer.accumulation_color_bits.b);
	glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, hints.framebuffer.accumulation_color_bits.a);
	glfwWindowHint(GLFW_AUX_BUFFERS, hints.framebuffer.auxiliary_buffers);
	glfwWindowHint(GLFW_STEREO, static_cast<int>(hints.framebuffer.stereo));
	glfwWindowHint(GLFW_SAMPLES, hints.framebuffer.samples);
	glfwWindowHint(GLFW_SRGB_CAPABLE, static_cast<int>(hints.framebuffer.srgb_capable));
	glfwWindowHint(GLFW_DOUBLEBUFFER, static_cast<int>(hints.framebuffer.doublebuffer));

	glfwWindowHint(GLFW_REFRESH_RATE, hints.monitor.refresh_rate);

	glfwWindowHint(GLFW_CLIENT_API, static_cast<int>(hints.context.client_api));
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, static_cast<int>(hints.context.creation_api));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hints.context.version.first);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hints.context.version.second);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, static_cast<int>(hints.context.opengl_forward_compat));
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, static_cast<int>(hints.context.debug));
	glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(hints.context.opengl_profile));
	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(hints.context.robustness));
	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, static_cast<int>(hints.context.release_behavior));
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, static_cast<int>(hints.context.no_error));

	glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, static_cast<int>(hints.win32.keyboard_menu));
	glfwWindowHint(GLFW_WIN32_SHOWDEFAULT, static_cast<int>(hints.win32.showdefault));

	glfwWindowHintString(GLFW_COCOA_FRAME_NAME, hints.cocoa.frame_name.c_str());
	glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, static_cast<int>(hints.cocoa.graphics_switching));

	glfwWindowHintString(GLFW_WAYLAND_APP_ID, hints.wayland.app_id.c_str());

	glfwWindowHintString(GLFW_X11_CLASS_NAME, hints.x11.class_name.c_str());
	glfwWindowHintString(GLFW_X11_INSTANCE_NAME, hints.x11.instance_name.c_str());
}

} // namespace void_engine::display::window
