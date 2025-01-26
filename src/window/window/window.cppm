module;

#include <GLFW/glfw3.h>

export module void_engine.window:window;

import :monitor;
import :window_hints;

import std;
import glm;

export namespace void_engine::window::input {
class InputManager;
} // namespace void_engine::window::input

export namespace void_engine::window {
class WindowEventHandler;
} // namespace void_engine::window

export namespace void_engine::window {

class Window {
public:
	Window(const Window&) = default;
	Window(Window&&) = default;
	auto operator=(const Window&) -> Window& = default;
	auto operator=(Window&&) -> Window& = default;
	Window(
		std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Window& share,
		const Hints& hints = {}
	);
	Window(
		std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints = {}
	);
	Window(
		std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints = {}
	);
	Window(std::string_view title, const glm::ivec2& size, const Hints& hints = {});
	~Window();

	void swap_buffers() const;

	void bind() const;
	static void unbind();

	void close() const;
	void focus() const;
	void hide() const;
	void show() const;

	void maximize() const;
	void minimize() const;
	void restore() const;

	void fullscreen() const;
	void fullscreen(const Monitor& monitor) const;
	void fullscreen(const Monitor& monitor, const VideoMode& video_mode) const;
	void windowed(const glm::ivec2& position, const glm::ivec2& size) const;

	void set_aspect_ratio(const glm::ivec2& ratio);
	void set_auto_minimize(bool enabled);
	void set_decoration(bool enabled);
	void set_floating(bool enabled);
	void set_focus_on_show(bool enabled);
	void set_icon(const std::filesystem::path& path);
	void set_icons(std::span<std::filesystem::path> paths);
	void set_opacity(float alpha);
	void set_position(const glm::ivec2& position);
	void set_resizable(bool enabled);
	void set_size(const glm::ivec2& size);
	void set_size_constraints(const glm::ivec2& min, const glm::ivec2& max);
	void set_title(std::string_view title);

	static void set_vsync(bool enabled);
	static void set_swap_interval(int interval);

	[[nodiscard]] auto get_events() -> WindowEventHandler&;
	[[nodiscard]] auto get_inputs() -> input::InputManager&;

	[[nodiscard]] auto get_content_scale() const -> glm::vec2;
	[[nodiscard]] auto get_frame_size() const -> std::tuple<glm::ivec2, glm::ivec2>;
	[[nodiscard]] auto get_framebuffer_position() const -> glm::ivec2;
	[[nodiscard]] auto get_framebuffer_size() const -> glm::ivec2;
	[[nodiscard]] auto get_opacity() const -> float;
	[[nodiscard]] auto get_position() const -> glm::ivec2;
	[[nodiscard]] auto get_size() const -> glm::ivec2;
	[[nodiscard]] auto get_title() const -> std::string_view;

	[[nodiscard]] auto has_focus_on_show() const -> bool;
	[[nodiscard]] auto has_mouse_passthrough() const -> bool;
	[[nodiscard]] auto has_transparent_framebuffer() const -> bool;
	[[nodiscard]] auto is_decorated() const -> bool;
	[[nodiscard]] auto is_floating() const -> bool;
	[[nodiscard]] auto is_focused() const -> bool;
	[[nodiscard]] auto is_hovered() const -> bool;
	[[nodiscard]] auto is_maximized() const -> bool;
	[[nodiscard]] auto is_minimized() const -> bool;
	[[nodiscard]] auto is_resizable() const -> bool;
	[[nodiscard]] auto is_visible() const -> bool;
	[[nodiscard]] auto scales_framebuffer_to_monitor() const -> bool;
	[[nodiscard]] auto scales_to_monitor() const -> bool;
	[[nodiscard]] auto should_close() const -> bool;

	[[nodiscard]] auto raw() const -> GLFWwindow*;

private:
	GLFWwindow* _window;
	WindowEventHandler* _events;
	input::InputManager* _inputs;

	Window(
		std::string_view title, const glm::ivec2& size, GLFWmonitor* monitor, GLFWwindow* share,
		const Hints& hints
	);

	static void apply_hints(const Hints& hints);
};

} // namespace void_engine::window
