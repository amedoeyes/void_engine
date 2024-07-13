#include "void_engine/window/inputs/mouse.hpp"

#include <glm/ext/vector_float2.hpp>

namespace void_engine::window::inputs {

void Mouse::update() {
	for (auto& [_, button] : _buttons) {
		button.previous = button.current;
	}
	_position.previous = _position.current;
}

void Mouse::set_button(MouseButton button, bool state) {
	_buttons[button].current = state;
}

void Mouse::set_position(const glm::vec2& position) {
	_position.current = position;
}

void Mouse::set_scroll(const glm::vec2& scroll) {
	_scroll = scroll;
}

auto Mouse::is_down(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return it->second.current;
}

auto Mouse::is_up(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return !it->second.current;
}

auto Mouse::is_pressed(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return it->second.current && !it->second.previous;
}

auto Mouse::get_position() const -> glm::vec2 {
	return _position.current;
}

auto Mouse::get_delta_position() const -> glm::vec2 {
	return _position.current - _position.previous;
}

auto Mouse::get_scroll() const -> glm::vec2 {
	return _scroll;
}

} // namespace void_engine::window::inputs
