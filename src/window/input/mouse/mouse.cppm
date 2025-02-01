module;

#include <GLFW/glfw3.h>

export module void_engine.window:input.mouse;

import :input.mouse_enums;
import :window_event_bus;

import std;
import glm;
import void_engine.utility.state;

export namespace void_engine::window {
class window;
}  // namespace void_engine::window

export namespace void_engine::window::input::mouse {

class Mouse {
public:
	Mouse(const Mouse&) = default;
	Mouse(Mouse&&) = default;
	auto operator=(const Mouse&) -> Mouse& = default;
	auto operator=(Mouse&&) -> Mouse& = default;
	explicit Mouse(window& window);
	~Mouse();

	void update();

	void set_button(Button button, bool state);
	void set_position(const glm::vec2& position);
	void set_scroll(const glm::vec2& scroll);
	void set_mode(Mode mode) const;
	void set_raw_motion(bool enabled) const;
	void set_shape(Shape shape);
	void set_image(const std::filesystem::path& path, const glm::vec2& hot_spot = {0.0f, 0.0f});

	[[nodiscard]]
	auto get_position() const -> glm::vec2;
	[[nodiscard]]
	auto get_delta_position() const -> glm::vec2;
	[[nodiscard]]
	auto get_scroll() const -> glm::vec2;

	[[nodiscard]]
	auto is_down(Button button) const -> bool;
	[[nodiscard]]
	auto is_up(Button button) const -> bool;
	[[nodiscard]]
	auto is_pressed(Button button) const -> bool;
	[[nodiscard]]
	auto is_released(Button button) const -> bool;

private:
	window* _window;
	GLFWcursor* _cursor = nullptr;
	std::array<utility::State<bool>, 4> _buttons;
	utility::State<glm::vec2> _position;
	glm::vec2 _scroll = {0.0f, 0.0f};
	window_event_bus::id_type _mouse_button_listener;
	window_event_bus::id_type _mouse_position_listener;
	window_event_bus::id_type _mouse_scroll_listener;
};

} // namespace void_engine::window::input::mouse
