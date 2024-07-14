#ifndef VOID_ENGINE_WINDOW_WINDOW_HPP
#define VOID_ENGINE_WINDOW_WINDOW_HPP

#include "void_engine/window/window_event_handler.hpp"
#include "void_engine/window/window_input_handler.hpp"

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string_view>

struct GLFWwindow;

namespace void_engine::monitor {
class Monitor;
}

namespace void_engine::window {

class Window {
	friend class WindowEventHandler;
	friend class WindowInputHandler;

public:
	Window(const Window&) = default;
	Window(Window&&) = delete;
	auto operator=(const Window&) -> Window& = default;
	auto operator=(Window&&) -> Window& = delete;
	Window(std::string_view title, const glm::vec2& size);
	~Window();

	[[nodiscard]] auto event_handler() -> WindowEventHandler&;
	[[nodiscard]] auto input_handler() -> WindowInputHandler&;

	void close() const;
	void focus() const;
	void make_context_current() const;
	void swap_buffers() const;
	void update();

	void show() const;
	void hide() const;

	void iconify() const;
	void maximize() const;
	void restore() const;

	void fullscreen() const;
	void fullscreen(const monitor::Monitor& monitor) const;
	void windowed(const glm::vec2& position, const glm::vec2& size) const;

	void set_aspect_ratio(int numerator, int denominator);
	void set_auto_iconify(bool value);
	void set_decorated(bool value);
	void set_floating(bool value);
	void set_focus_on_show(bool value);
	void set_opacity(float opacity);
	void set_position(const glm::vec2& position);
	void set_resizable(bool value);
	void set_size(const glm::vec2& size);
	void set_size_limits(const glm::vec2& min, const glm::vec2& max);
	void set_title(std::string_view title);

	[[nodiscard]] auto get_content_scale() const -> glm::vec2;
	[[nodiscard]] auto get_frame_size() const -> glm::vec4;
	[[nodiscard]] auto get_framebuffer_position() const -> glm::vec2;
	[[nodiscard]] auto get_framebuffer_size() const -> glm::vec2;
	[[nodiscard]] auto get_opacity() const -> float;
	[[nodiscard]] auto get_position() const -> glm::vec2;
	[[nodiscard]] auto get_size() const -> glm::vec2;
	[[nodiscard]] auto get_title() const -> std::string;

	[[nodiscard]] auto is_auto_iconified() const -> bool;
	[[nodiscard]] auto is_close_requested() const -> bool;
	[[nodiscard]] auto is_decorated() const -> bool;
	[[nodiscard]] auto is_floating() const -> bool;
	[[nodiscard]] auto is_focus_on_show() const -> bool;
	[[nodiscard]] auto is_focused() const -> bool;
	[[nodiscard]] auto is_hovered() const -> bool;
	[[nodiscard]] auto is_iconified() const -> bool;
	[[nodiscard]] auto is_maximized() const -> bool;
	[[nodiscard]] auto is_mouse_passthrough() const -> bool;
	[[nodiscard]] auto is_resizable() const -> bool;
	[[nodiscard]] auto is_scale_framebuffer() const -> bool;
	[[nodiscard]] auto is_scale_to_monitor() const -> bool;
	[[nodiscard]] auto is_transparent_framebuffer() const -> bool;
	[[nodiscard]] auto is_visible() const -> bool;

private:
	GLFWwindow* _window;
	WindowEventHandler* _event_handler;
	WindowInputHandler* _input_handler;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_HPP
