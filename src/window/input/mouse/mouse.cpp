module;

#include <cassert>
#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;
import void_engine.resources;

namespace void_engine::window::input {

auto mouse::update() -> void {
	for (auto& button : buttons_) button.set_previous(button.current());
	position_.set_previous(position_.current());
}

auto mouse::set_button(mouse_button button, bool state) -> void {
	buttons_.at(std::to_underlying(button)).set_current(state);
}

auto mouse::set_position(const glm::vec2& position) -> void {
	position_.set_current(position);
}

auto mouse::set_scroll(const glm::vec2& scroll) -> void {
	scroll_ = scroll;
}

auto mouse::position() const -> glm::vec2 {
	return position_.current();
}

auto mouse::delta_position() const -> glm::vec2 {
	return position_.current() - position_.previous();
}

auto mouse::scroll() const -> glm::vec2 {
	return scroll_;
}

auto mouse::is_down(mouse_button button) const -> bool {
	return buttons_.at(std::to_underlying(button)).current();
}

auto mouse::is_up(mouse_button button) const -> bool {
	return !buttons_.at(std::to_underlying(button)).current();
}

auto mouse::is_pressed(mouse_button button) const -> bool {
	return buttons_.at(std::to_underlying(button)).entered(true);
}

auto mouse::is_released(mouse_button button) const -> bool {
	return buttons_.at(std::to_underlying(button)).exited(true);
}

} // namespace void_engine::window::input
