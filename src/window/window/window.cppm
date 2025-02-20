module;

#include <cassert>
#include <GLFW/glfw3.h>

export module void_engine.window:window;

import :monitor;
import :window_enums;
import :window_event_bus;
import :window_hints;
import :window_inputs;

import glm;
import std;
import void_engine.resources;
import void_engine.utility;

namespace void_engine::window {

auto apply_hints(const window_hints& hints) -> void {
	glfwWindowHint(GLFW_RESIZABLE, static_cast<int>(hints.window.resizable));
	glfwWindowHint(GLFW_VISIBLE, static_cast<int>(hints.window.visible));
	glfwWindowHint(GLFW_DECORATED, static_cast<int>(hints.window.decorated));
	glfwWindowHint(GLFW_FOCUSED, static_cast<int>(hints.window.focused));
	glfwWindowHint(GLFW_AUTO_ICONIFY, static_cast<int>(hints.window.auto_iconify));
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

export namespace void_engine::window {

class window {
public:
	window(std::string_view title,
	       const glm::ivec2& size,
	       const monitor& monitor,
	       const window& share,
	       const window_hints& hints = {}) {
		init(title, size, monitor.raw(), share.raw(), hints);
	}

	window(std::string_view title, const glm::ivec2& size, const monitor& monitor, const window_hints& hints = {}) {
		init(title, size, monitor.raw(), nullptr, hints);
	}

	window(std::string_view title, const glm::ivec2& size, const window& share, const window_hints& hints = {}) {
		init(title, size, nullptr, share.raw(), hints);
	}

	window(std::string_view title, const glm::ivec2& size, const window_hints& hints = {}) {
		init(title, size, nullptr, nullptr, hints);
	}

	auto swap_buffers() const -> void {
		glfwSwapBuffers(window_.get());
	}

	auto close() const -> void {
		glfwSetWindowShouldClose(window_.get(), 1);
	}

	auto focus() const -> void {
		glfwFocusWindow(window_.get());
	}

	auto hide() const -> void {
		glfwHideWindow(window_.get());
	}

	auto show() const -> void {
		glfwShowWindow(window_.get());
	}

	auto maximize() const -> void {
		glfwMaximizeWindow(window_.get());
	}

	auto iconify() const -> void {
		glfwIconifyWindow(window_.get());
	}

	auto restore() const -> void {
		glfwRestoreWindow(window_.get());
	}

	auto fullscreen() const -> void {
		auto* monitor = glfwGetPrimaryMonitor();
		const auto* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window_.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}

	auto fullscreen(const monitor& monitor) const -> void {
		const auto& mode = monitor.current_video_mode();
		glfwSetWindowMonitor(window_.get(), monitor.raw(), 0, 0, mode.size.x, mode.size.y, mode.refresh_rate);
	}

	auto fullscreen(const monitor& monitor, const video_mode& video_mode) const -> void {
		glfwSetWindowMonitor(window_.get(),
		                     monitor.raw(),
		                     0,
		                     0,
		                     video_mode.size.x,
		                     video_mode.size.y,
		                     video_mode.refresh_rate);
	}

	auto windowed(const glm::ivec2& position, const glm::ivec2& size) const -> void {
		glfwSetWindowMonitor(window_.get(), nullptr, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);
	}

	auto set_aspect_ratio(const glm::ivec2& ratio) -> void {
		glfwSetWindowAspectRatio(window_.get(), ratio.x, ratio.y);
	}

	auto set_auto_iconify(bool enabled) -> void {
		glfwSetWindowAttrib(window_.get(), GLFW_AUTO_ICONIFY, static_cast<int>(enabled));
	}

	auto set_current_context() const -> void {
		glfwMakeContextCurrent(window_.get());
	}

	auto set_decoration(bool enabled) -> void {
		glfwSetWindowAttrib(window_.get(), GLFW_DECORATED, static_cast<int>(enabled));
	}

	auto set_floating(bool enabled) -> void {
		glfwSetWindowAttrib(window_.get(), GLFW_FLOATING, static_cast<int>(enabled));
	}

	auto set_focus_on_show(bool enabled) -> void {
		glfwSetWindowAttrib(window_.get(), GLFW_FOCUS_ON_SHOW, static_cast<int>(enabled));
	}

	auto set_icon(const resources::image& image) -> void {
		glfwSetWindowIcon(window_.get(), 0, nullptr);
		const auto glfw_image = GLFWimage{
			.width = image.size().x,
			.height = image.size().y,
			.pixels = std::bit_cast<unsigned char*>(image.data().data()),
		};
		glfwSetWindowIcon(window_.get(), 1, &glfw_image);
	}

	auto set_icons(std::span<resources::image> images) -> void {
		const auto glfw_images = images //
		                       | std::views::transform([](const auto& image) {
															 return GLFWimage{
																 .width = image.size().x,
																 .height = image.size().y,
																 .pixels = std::bit_cast<unsigned char*>(image.data().data()),
															 };
														 })
		                       | std::ranges::to<std::vector>();
		glfwSetWindowIcon(window_.get(), static_cast<int>(glfw_images.size()), glfw_images.data());
	}

	auto set_opacity(float alpha) -> void {
		glfwSetWindowOpacity(window_.get(), alpha);
	}

	auto set_position(const glm::ivec2& position) -> void {
		glfwSetWindowPos(window_.get(), position.x, position.y);
	}

	auto set_resizable(bool enabled) -> void {
		glfwSetWindowAttrib(window_.get(), GLFW_RESIZABLE, static_cast<int>(enabled));
	}

	auto set_size(const glm::ivec2& size) -> void {
		glfwSetWindowSize(window_.get(), size.x, size.y);
	}

	auto set_size_constraints(const glm::ivec2& min, const glm::ivec2& max) -> void {
		glfwSetWindowSizeLimits(window_.get(), min.x, min.y, max.x, max.y);
	}

	auto set_title(std::string_view title) -> void {
		glfwSetWindowTitle(window_.get(), std::string(title).c_str());
	}

	[[nodiscard]]
	auto events() -> window_event_bus& {
		return events_;
	}

	[[nodiscard]]
	auto inputs() -> window_inputs& {
		return inputs_;
	}

	[[nodiscard]]
	auto content_scale() const -> glm::vec2 {
		auto scale = glm::vec2{};
		glfwGetWindowContentScale(window_.get(), &scale.x, &scale.y);
		return scale;
	}

	[[nodiscard]]
	auto frame_size() const -> std::pair<glm::ivec2, glm::ivec2> {
		auto position = glm::ivec2{};
		auto size = glm::ivec2{};
		glfwGetWindowFrameSize(window_.get(), &position.x, &position.y, &size.x, &size.y);
		return {position, size};
	}

	[[nodiscard]]
	auto framebuffer_size() const -> glm::ivec2 {
		auto size = glm::ivec2{};
		glfwGetFramebufferSize(window_.get(), &size.x, &size.y);
		return size;
	}

	[[nodiscard]]
	auto opacity() const -> float {
		return glfwGetWindowOpacity(window_.get());
	}

	[[nodiscard]]
	auto position() const -> glm::ivec2 {
		auto position = glm::ivec2{};
		glfwGetWindowPos(window_.get(), &position.x, &position.y);
		return position;
	}

	[[nodiscard]]
	auto size() const -> glm::ivec2 {
		auto size = glm::ivec2{};
		glfwGetWindowSize(window_.get(), &size.x, &size.y);
		return size;
	}

	[[nodiscard]]
	auto title() const -> std::string_view {
		return glfwGetWindowTitle(window_.get());
	}

	[[nodiscard]]
	auto has_focus_on_show() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_FOCUS_ON_SHOW) != 0;
	}

	[[nodiscard]]
	auto has_mouse_passthrough() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_MOUSE_PASSTHROUGH) != 0;
	}

	[[nodiscard]]
	auto has_transparent_framebuffer() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_TRANSPARENT_FRAMEBUFFER) != 0;
	}

	[[nodiscard]]
	auto is_decorated() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_DECORATED) != 0;
	}

	[[nodiscard]]
	auto is_floating() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_FLOATING) != 0;
	}

	[[nodiscard]]
	auto is_focused() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_FOCUSED) != 0;
	}

	[[nodiscard]]
	auto is_maximized() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_MAXIMIZED) != 0;
	}

	[[nodiscard]]
	auto is_iconified() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_ICONIFIED) != 0;
	}

	[[nodiscard]]
	auto is_resizable() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_RESIZABLE) != 0;
	}

	[[nodiscard]]
	auto is_visible() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_VISIBLE) != 0;
	}

	[[nodiscard]]
	auto scales_framebuffer_to_monitor() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_SCALE_FRAMEBUFFER) != 0;
	}

	[[nodiscard]]
	auto scales_to_monitor() const -> bool {
		return glfwGetWindowAttrib(window_.get(), GLFW_SCALE_TO_MONITOR) != 0;
	}

	[[nodiscard]]
	auto should_close() const -> bool {
		return glfwWindowShouldClose(window_.get()) != 0;
	}

	[[nodiscard]]
	auto raw() const -> GLFWwindow* {
		return window_.get();
	}

	auto set_cursor_mode(cursor_mode mode) const -> void {
		glfwSetInputMode(window_.get(), GLFW_CURSOR, std::to_underlying(mode));
	}

	auto set_cursor_raw_motion(bool enabled) const -> void {
		glfwSetInputMode(window_.get(), GLFW_RAW_MOUSE_MOTION, static_cast<int>(enabled));
	}

	auto set_cursor_shape(cursor_shape shape) -> void {
		cursor_.reset(glfwCreateStandardCursor(std::to_underlying(shape)));
		assert(cursor_ != nullptr && "Failed to create cursor");
		glfwSetCursor(window_.get(), cursor_.get());
	}

	auto set_cursor_image(const resources::image& image, const glm::ivec2& hot_spot = {0, 0}) -> void {
		const auto glfw_image = GLFWimage{
			.width = image.size().x,
			.height = image.size().y,
			.pixels = std::bit_cast<unsigned char*>(image.data().data()),
		};
		cursor_.reset(glfwCreateCursor(&glfw_image, hot_spot.x, hot_spot.y));
		assert(cursor_ != nullptr && "Failed to create cursor");
		glfwSetCursor(window_.get(), cursor_.get());
	}

private:
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window_{nullptr, &glfwDestroyWindow};
	std::unique_ptr<GLFWcursor, decltype(&glfwDestroyCursor)> cursor_{nullptr, &glfwDestroyCursor};
	window_event_bus events_;
	window_inputs inputs_;

	auto init_events() -> void {
		static const auto emit = [this](auto&& data) { return events_.emit(std::forward<decltype(data)>(data)); };
		auto* window = window_.get();
		glfwSetDropCallback(window, [](auto*, auto count, const char** paths) {
			emit(event::drop{
				std::span(paths, count) //
					| std::views::transform([](auto&& path) { return std::filesystem::path(path); })
					| std::ranges::to<std::vector>(),
			});
		});
		glfwSetFramebufferSizeCallback(window, [](auto*, auto w, auto h) { emit(event::framebuffer_size{{w, h}}); });
		glfwSetCharCallback(window, [](auto*, auto codepoint) { emit(event::keyboard_char{codepoint}); });
		glfwSetCharModsCallback(window, [](auto*, auto codepoint, auto mods) {
			emit(event::keyboard_char_mods{.codepoint = codepoint, .mods = mods});
		});
		glfwSetKeyCallback(window, [](auto*, auto key, auto scancode, auto action, auto mods) {
			emit(event::keyboard_key{
				.key = static_cast<input::keyboard_key>(key),
				.scancode = scancode,
				.action = static_cast<input::keyboard_action>(action),
				.mods = utility::BitMask<input::keyboard_mod>(mods),
			});
		});
		glfwSetMouseButtonCallback(window, [](auto*, auto button, auto action, auto mods) {
			emit(event::mouse_button{
				.button = static_cast<input::mouse_button>(button),
				.action = static_cast<input::mouse_action>(action),
				.mods = utility::BitMask<input::keyboard_mod>(mods),
			});
		});
		glfwSetCursorEnterCallback(window, [](auto*, auto entered) { emit(event::mouse_enter{entered == 1}); });
		glfwSetCursorPosCallback(window, [](auto*, auto x, auto y) { emit(event::mouse_position{{x, y}}); });
		glfwSetScrollCallback(window, [](auto*, auto x, auto y) { emit(event::mouse_scroll{{x, y}}); });
		glfwSetWindowCloseCallback(window, [](auto*) { emit(event::window_close{}); });
		glfwSetWindowContentScaleCallback(window,
		                                  [](auto*, float x, float y) { emit(event::window_content_scale{{x, y}}); });
		glfwSetWindowFocusCallback(window, [](auto*, auto focused) { emit(event::window_focus{focused == 1}); });
		glfwSetWindowIconifyCallback(window, [](auto*, auto iconified) { emit(event::window_iconify{iconified == 1}); });
		glfwSetWindowMaximizeCallback(window, [](auto*, auto maximized) { emit(event::window_maximize{maximized == 1}); });
		glfwSetWindowPosCallback(window, [](auto*, auto x, auto y) { emit(event::window_position{{x, y}}); });
		glfwSetWindowRefreshCallback(window, [](auto*) { emit(event::window_refresh{}); });
		glfwSetWindowSizeCallback(window, [](auto*, auto w, auto h) { emit(event::window_size{{w, h}}); });
	}

	auto init_inputs() -> void {
		events_.add_listener<event::keyboard_key>([this](const auto& event) {
			inputs_.keyboard.set_key(event.key,
			                         event.action == input::keyboard_action::press
			                           || event.action == input::keyboard_action::repeat);
		});

		events_.add_listener<event::mouse_button>([&](const auto& event) {
			inputs_.mouse.set_button(event.button, event.action == input::mouse_action::press);
		});
		events_.add_listener<event::mouse_position>([&](const auto& event) { inputs_.mouse.set_position(event.position); });
		events_.add_listener<event::mouse_scroll>([&](const auto& event) { inputs_.mouse.set_scroll(event.offset); });
	}

	auto init(std::string_view title,
	          const glm::ivec2& size,
	          GLFWmonitor* monitor,
	          GLFWwindow* share,
	          const window_hints& hints) -> void {
		apply_hints(hints);
		window_.reset(glfwCreateWindow(size.x, size.y, std::string(title).c_str(), monitor, share));
		assert(window_ != nullptr && "Failed to create window");
		glfwMakeContextCurrent(window_.get());
		glfwSetWindowUserPointer(window_.get(), this);
		init_events();
		init_inputs();
	}
};

} // namespace void_engine::window
