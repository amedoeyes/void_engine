module;

#include <GLFW/glfw3.h>

export module void_engine.window:window;

import :input.input_manager;
import :monitor;
import :window_event_bus;
import :window_hints;

import glm;
import std;

export namespace void_engine::window {

class window {
public:
	window(std::string_view title,
	       const glm::ivec2& size,
	       const Monitor& monitor,
	       const window& share,
	       const window_hints& hints = {});
	window(std::string_view title, const glm::ivec2& size, const Monitor& monitor, const window_hints& hints = {});
	window(std::string_view title, const glm::ivec2& size, const window& share, const window_hints& hints = {});
	window(std::string_view title, const glm::ivec2& size, const window_hints& hints = {});

	auto swap_buffers() const -> void;

	auto close() const -> void;

	auto focus() const -> void;

	auto hide() const -> void;

	auto show() const -> void;

	auto maximize() const -> void;

	auto iconify() const -> void;

	auto restore() const -> void;

	auto fullscreen() const -> void;

	auto fullscreen(const Monitor& monitor) const -> void;

	auto fullscreen(const Monitor& monitor, const VideoMode& video_mode) const -> void;

	auto windowed(const glm::ivec2& position, const glm::ivec2& size) const -> void;

	auto set_aspect_ratio(const glm::ivec2& ratio) -> void;

	auto set_auto_iconify(bool enabled) -> void;

	auto set_current_context() const -> void;

	auto set_decoration(bool enabled) -> void;

	auto set_floating(bool enabled) -> void;

	auto set_focus_on_show(bool enabled) -> void;

	auto set_icon(const std::filesystem::path& path) -> void;

	auto set_icons(std::span<std::filesystem::path> paths) -> void;

	auto set_opacity(float alpha) -> void;

	auto set_position(const glm::ivec2& position) -> void;

	auto set_resizable(bool enabled) -> void;

	auto set_size(const glm::ivec2& size) -> void;

	auto set_size_constraints(const glm::ivec2& min, const glm::ivec2& max) -> void;

	auto set_title(std::string_view title) -> void;

	[[nodiscard]]
	auto events() -> window_event_bus&;

	[[nodiscard]]
	auto inputs() -> input::input_manager&;

	[[nodiscard]]
	auto content_scale() const -> glm::vec2;

	[[nodiscard]]
	auto frame_size() const -> std::pair<glm::ivec2, glm::ivec2>;

	[[nodiscard]]
	auto framebuffer_size() const -> glm::ivec2;

	[[nodiscard]]
	auto opacity() const -> float;

	[[nodiscard]]
	auto position() const -> glm::ivec2;

	[[nodiscard]]
	auto size() const -> glm::ivec2;

	[[nodiscard]]
	auto title() const -> std::string_view;

	[[nodiscard]]
	auto has_focus_on_show() const -> bool;

	[[nodiscard]]
	auto has_mouse_passthrough() const -> bool;

	[[nodiscard]]
	auto has_transparent_framebuffer() const -> bool;

	[[nodiscard]]
	auto is_decorated() const -> bool;

	[[nodiscard]]
	auto is_floating() const -> bool;

	[[nodiscard]]
	auto is_focused() const -> bool;

	[[nodiscard]]
	auto is_hovered() const -> bool;

	[[nodiscard]]
	auto is_maximized() const -> bool;

	[[nodiscard]]
	auto is_iconified() const -> bool;

	[[nodiscard]]
	auto is_resizable() const -> bool;

	[[nodiscard]]
	auto is_visible() const -> bool;

	[[nodiscard]]
	auto scales_framebuffer_to_monitor() const -> bool;

	[[nodiscard]]
	auto scales_to_monitor() const -> bool;

	[[nodiscard]]
	auto should_close() const -> bool;

	[[nodiscard]]
	auto raw() const -> GLFWwindow*;

private:
	struct destroy_glfw_window {
		void operator()(GLFWwindow* w) { glfwDestroyWindow(w); }
	};

	std::unique_ptr<GLFWwindow, destroy_glfw_window> _window;
	std::unique_ptr<window_event_bus> _events;
	std::unique_ptr<input::input_manager> _inputs;

	window(std::string_view title,
	       const glm::ivec2& size,
	       GLFWmonitor* monitor,
	       GLFWwindow* share,
	       const window_hints& hints);

	static auto apply_hints(const window_hints& hints) -> void;
};

} // namespace void_engine::window
