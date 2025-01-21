#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_HPP

#include "void_engine/display/monitor/video_mode.hpp"
#include "void_engine/display/window/hints.hpp"
#include "void_engine/display/window/input/mouse/mouse.hpp"
#include "void_engine/display/window/window_event_handler.hpp"
#include "void_engine/display/window/window_input_handler.hpp"

#include <filesystem>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <span>
#include <string_view>
#include <tuple>

struct GLFWwindow;
struct GLFWmonitor;

namespace void_engine::display::monitor {
class Monitor;
}

namespace void_engine::display::window {

class Window {
	friend class WindowEventHandler;
	friend class input::mouse::Mouse;

public:
	Window(const Window&) = default;
	Window(Window&&) = delete;
	auto operator=(const Window&) -> Window& = default;
	auto operator=(Window&&) -> Window& = delete;
	Window(
		std::string_view title, const glm::ivec2& size, const monitor::Monitor& monitor,
		const Window& share, const Hints& hints = {}
	);
	Window(
		std::string_view title, const glm::ivec2& size, const monitor::Monitor& monitor,
		const Hints& hints = {}
	);
	Window(
		std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints = {}
	);
	Window(std::string_view title, const glm::ivec2& size, const Hints& hints = {});
	~Window();

	void update();
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
	void fullscreen(const monitor::Monitor& monitor) const;
	void fullscreen(const monitor::Monitor& monitor, const monitor::VideoMode& video_mode) const;
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

	[[nodiscard]] auto get_event_handler() -> WindowEventHandler&;
	[[nodiscard]] auto get_input_handler() -> WindowInputHandler&;

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

private:
	GLFWwindow* _window;
	WindowEventHandler* _event_handler;
	WindowInputHandler* _input_handler;

	Window(
		std::string_view title, const glm::ivec2& size, GLFWmonitor* monitor, GLFWwindow* share,
		const Hints& hints
	);

	static void apply_hints(const Hints& hints);
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_HPP
