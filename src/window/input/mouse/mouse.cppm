module;

#include <GLFW/glfw3.h>

export module void_engine.window:input.mouse;

import :input.mouse_enums;
import :window_event_bus;

import std;
import glm;
import void_engine.utility.state;
import void_engine.resources;

export namespace void_engine::window {
class window;
}  // namespace void_engine::window

export namespace void_engine::window::input {

// PERF: it would be better if we cache shapes and images
class mouse {
public:
	mouse(const mouse&) = delete;
	mouse(mouse&&) = default;
	auto operator=(const mouse&) -> mouse& = delete;
	auto operator=(mouse&&) -> mouse& = default;
	explicit mouse(window& window);
	~mouse();

	auto update() -> void;

	auto set_button(mouse_button button, bool state) -> void;

	auto set_position(const glm::vec2& position) -> void;

	auto set_scroll(const glm::vec2& scroll) -> void;

	auto set_mode(mouse_mode mode) const -> void;

	auto set_raw_motion(bool enabled) const -> void;

	auto set_shape(mouse_shape shape) -> void;

	auto set_image(const resources::Image& image, const glm::ivec2& hot_spot = {0, 0}) -> void;

	[[nodiscard]]
	auto position() const -> glm::vec2;

	[[nodiscard]]
	auto delta_position() const -> glm::vec2;

	[[nodiscard]]
	auto scroll() const -> glm::vec2;

	[[nodiscard]]
	auto is_down(mouse_button button) const -> bool;

	[[nodiscard]]
	auto is_up(mouse_button button) const -> bool;

	[[nodiscard]]
	auto is_pressed(mouse_button button) const -> bool;

	[[nodiscard]]
	auto is_released(mouse_button button) const -> bool;

private:
	struct destroy_glfw_cursor {
		auto operator()(GLFWcursor* c) -> void {
			glfwDestroyCursor(c);
		}
	};

	std::reference_wrapper<window> window_;
	std::unique_ptr<GLFWcursor, destroy_glfw_cursor> cursor_;
	std::array<utility::state<bool>, 4> buttons_;
	utility::state<glm::vec2> position_;
	glm::vec2 scroll_ = {0.0f, 0.0f};
	window_event_bus::id_type button_listener_id_;
	window_event_bus::id_type position_listener_id_;
	window_event_bus::id_type scroll_listener_id_;
};

} // namespace void_engine::window::input
