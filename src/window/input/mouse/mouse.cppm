module;

#include <GLFW/glfw3.h>

export module void_engine.window:input.mouse;

import :input.mouse_enums;

import std;
import glm;
import void_engine.utility.state;
import void_engine.resources;

export namespace void_engine::window::input {

// PERF: it would be better if we cache shapes and images
class mouse {
public:
	auto update() -> void;

	auto set_button(mouse_button button, bool state) -> void;

	auto set_position(const glm::vec2& position) -> void;

	auto set_scroll(const glm::vec2& scroll) -> void;

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
	std::array<utility::state<bool>, 4> buttons_;
	utility::state<glm::vec2> position_;
	glm::vec2 scroll_ = {0.0f, 0.0f};
};

} // namespace void_engine::window::input
