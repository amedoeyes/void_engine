module;

#include <cassert>
#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;
import void_engine.resources;

namespace void_engine::window {

window::window(
	std::string_view title, const glm::ivec2& size, const Monitor& monitor, const window& share, const Hints& hints
)
	: window(title, size, monitor.raw(), share.raw(), hints) {}

window::window(std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints)
	: window(title, size, monitor.raw(), nullptr, hints) {}

window::window(std::string_view title, const glm::ivec2& size, const window& share, const Hints& hints)
	: window(title, size, nullptr, share.raw(), hints) {}

window::window(std::string_view title, const glm::ivec2& size, const Hints& hints)
	: window(title, size, nullptr, nullptr, hints) {}

window::window(
	std::string_view title, const glm::ivec2& size, GLFWmonitor* monitor, GLFWwindow* share, const Hints& hints
) {
	apply_hints(hints);
	_window.reset(glfwCreateWindow(size.x, size.y, std::string(title).c_str(), monitor, share));
	assert(_window != nullptr && "Failed to create window");
	glfwMakeContextCurrent(_window.get());
	glfwSetWindowUserPointer(_window.get(), this);
	_events = std::make_unique<WindowEventHandler>(*this);
	_inputs = std::make_unique<input::InputManager>(*this);
}

auto window::swap_buffers() const -> void { glfwSwapBuffers(_window.get()); }

auto window::close() const -> void { glfwSetWindowShouldClose(_window.get(), 1); }

auto window::focus() const -> void { glfwFocusWindow(_window.get()); }

auto window::hide() const -> void { glfwHideWindow(_window.get()); }

auto window::show() const -> void { glfwShowWindow(_window.get()); }

auto window::maximize() const -> void { glfwMaximizeWindow(_window.get()); }

auto window::minimize() const -> void { glfwIconifyWindow(_window.get()); }

auto window::restore() const -> void { glfwRestoreWindow(_window.get()); }

auto window::fullscreen() const -> void {
	auto* monitor = glfwGetPrimaryMonitor();
	const auto* mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(_window.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

auto window::fullscreen(const Monitor& monitor) const -> void {
	const auto& mode = monitor.get_video_mode();
	glfwSetWindowMonitor(_window.get(), monitor.raw(), 0, 0, mode.size.x, mode.size.y, mode.refresh_rate);
}

auto window::fullscreen(const Monitor& monitor, const VideoMode& video_mode) const -> void {
	glfwSetWindowMonitor(
		_window.get(), monitor.raw(), 0, 0, video_mode.size.x, video_mode.size.y, video_mode.refresh_rate
	);
}

auto window::windowed(const glm::ivec2& position, const glm::ivec2& size) const -> void {
	glfwSetWindowMonitor(_window.get(), nullptr, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);
}

auto window::set_aspect_ratio(const glm::ivec2& ratio) -> void {
	glfwSetWindowAspectRatio(_window.get(), ratio.x, ratio.y);
}

auto window::set_auto_minimize(bool enabled) -> void {
	glfwSetWindowAttrib(_window.get(), GLFW_AUTO_ICONIFY, static_cast<int>(enabled));
}

auto window::set_current_context() const -> void { glfwMakeContextCurrent(_window.get()); }

auto window::set_decoration(bool enabled) -> void {
	glfwSetWindowAttrib(_window.get(), GLFW_DECORATED, static_cast<int>(enabled));
}

auto window::set_floating(bool enabled) -> void {
	glfwSetWindowAttrib(_window.get(), GLFW_FLOATING, static_cast<int>(enabled));
}

auto window::set_focus_on_show(bool enabled) -> void {
	glfwSetWindowAttrib(_window.get(), GLFW_FOCUS_ON_SHOW, static_cast<int>(enabled));
}

auto window::set_icon(const std::filesystem::path& path) -> void {
	glfwSetWindowIcon(_window.get(), 0, nullptr);
	const auto image = resources::Image(path, true);
	const auto& size = image.get_size();
	const auto glfw_image = GLFWimage{
		.width = size.x,
		.height = size.y,
		.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
	};
	glfwSetWindowIcon(_window.get(), 1, &glfw_image);
}

auto window::set_icons(std::span<std::filesystem::path> paths) -> void {
	auto images = std::vector<GLFWimage>{};
	images.reserve(paths.size());
	for (const auto& path : paths) {
		const auto image = resources::Image(path, true);
		const auto& size = image.get_size();
		images.push_back({
			.width = size.x,
			.height = size.y,
			.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
		});
	}
	glfwSetWindowIcon(_window.get(), static_cast<int>(images.size()), images.data());
}

auto window::set_opacity(float alpha) -> void { glfwSetWindowOpacity(_window.get(), alpha); }

auto window::set_position(const glm::ivec2& position) -> void {
	glfwSetWindowPos(_window.get(), position.x, position.y);
}

auto window::set_resizable(bool enabled) -> void {
	glfwSetWindowAttrib(_window.get(), GLFW_RESIZABLE, static_cast<int>(enabled));
}

auto window::set_size(const glm::ivec2& size) -> void { glfwSetWindowSize(_window.get(), size.x, size.y); }

auto window::set_size_constraints(const glm::ivec2& min, const glm::ivec2& max) -> void {
	glfwSetWindowSizeLimits(_window.get(), min.x, min.y, max.x, max.y);
}

auto window::set_title(std::string_view title) -> void {
	glfwSetWindowTitle(_window.get(), std::string(title).c_str());
}

auto window::events() -> WindowEventHandler& { return *_events; }

auto window::inputs() -> input::InputManager& { return *_inputs; }

auto window::content_scale() const -> glm::vec2 {
	auto scale = glm::vec2{};
	glfwGetWindowContentScale(_window.get(), &scale.x, &scale.y);
	return scale;
}

auto window::frame_size() const -> std::pair<glm::ivec2, glm::ivec2> {
	auto position = glm::ivec2{};
	auto size = glm::ivec2{};
	glfwGetWindowFrameSize(_window.get(), &position.x, &position.y, &size.x, &size.y);
	return {position, size};
}

auto window::framebuffer_size() const -> glm::ivec2 {
	auto size = glm::ivec2{};
	glfwGetFramebufferSize(_window.get(), &size.x, &size.y);
	return size;
}

auto window::opacity() const -> float { return glfwGetWindowOpacity(_window.get()); }

auto window::position() const -> glm::ivec2 {
	auto position = glm::ivec2{};
	glfwGetWindowPos(_window.get(), &position.x, &position.y);
	return position;
}

auto window::size() const -> glm::ivec2 {
	auto size = glm::ivec2{};
	glfwGetWindowSize(_window.get(), &size.x, &size.y);
	return size;
}

auto window::title() const -> std::string_view { return glfwGetWindowTitle(_window.get()); }

auto window::has_focus_on_show() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_FOCUS_ON_SHOW) != 0; }

auto window::has_mouse_passthrough() const -> bool {
	return glfwGetWindowAttrib(_window.get(), GLFW_MOUSE_PASSTHROUGH) != 0;
}

auto window::has_transparent_framebuffer() const -> bool {
	return glfwGetWindowAttrib(_window.get(), GLFW_TRANSPARENT_FRAMEBUFFER) != 0;
}

auto window::is_decorated() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_DECORATED) != 0; }

auto window::is_floating() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_FLOATING) != 0; }

auto window::is_focused() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_FOCUSED) != 0; }

auto window::is_maximized() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_MAXIMIZED) != 0; }

auto window::is_minimized() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_ICONIFIED) != 0; }

auto window::is_resizable() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_RESIZABLE) != 0; }

auto window::is_visible() const -> bool { return glfwGetWindowAttrib(_window.get(), GLFW_VISIBLE) != 0; }

auto window::scales_framebuffer_to_monitor() const -> bool {
	return glfwGetWindowAttrib(_window.get(), GLFW_SCALE_FRAMEBUFFER) != 0;
}

auto window::scales_to_monitor() const -> bool {
	return glfwGetWindowAttrib(_window.get(), GLFW_SCALE_TO_MONITOR) != 0;
}

auto window::should_close() const -> bool { return glfwWindowShouldClose(_window.get()) != 0; }

auto window::raw() const -> GLFWwindow* { return _window.get(); }

auto window::apply_hints(const Hints& hints) -> void {
	glfwWindowHint(GLFW_RESIZABLE, static_cast<int>(hints.window.resizable));
	glfwWindowHint(GLFW_VISIBLE, static_cast<int>(hints.window.visible));
	glfwWindowHint(GLFW_DECORATED, static_cast<int>(hints.window.decorated));
	glfwWindowHint(GLFW_FOCUSED, static_cast<int>(hints.window.focused));
	glfwWindowHint(GLFW_AUTO_ICONIFY, static_cast<int>(hints.window.auto_minimize));
	glfwWindowHint(GLFW_FLOATING, static_cast<int>(hints.window.floating));
	glfwWindowHint(GLFW_MAXIMIZED, static_cast<int>(hints.window.maximized));
	glfwWindowHint(GLFW_CENTER_CURSOR, static_cast<int>(hints.window.center_cursor));
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, static_cast<int>(hints.window.transparent_framebuffer));
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

}  // namespace void_engine::window
