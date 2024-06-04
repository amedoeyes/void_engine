#include "void_engine/input/mouse.hpp"

#include "void_engine/input/input_handler.hpp"

#include <cstdio>

namespace void_engine::input {

void Mouse::update() {
	_prev_states = _states;
}

auto Mouse::is_down(MouseButton button) const -> bool {
	return get_state(button);
}

auto Mouse::is_up(MouseButton button) const -> bool {
	return !get_state(button);
}

auto Mouse::is_pressed(MouseButton button) const -> bool {
	return get_state(button) && !get_prev_state(button);
}

auto Mouse::get_state(MouseButton button) const -> bool {
	auto it = _states.find(button);
	if (it == _states.end()) return false;
	return it->second;
}

void Mouse::set_state(MouseButton button, bool state) {
	_states[button] = state;
}

auto Mouse::get_prev_state(MouseButton button) const -> bool {
	auto it = _prev_states.find(button);
	if (it == _prev_states.end()) return false;
	return it->second;
}

void Mouse::set_prev_state(MouseButton button, bool state) {
	_prev_states[button] = state;
}

auto Mouse::get_position() const -> glm::vec2 {
	return _position;
}

void Mouse::set_position(float x, float y) {
	_position = {x, y};
}

auto Mouse::get_scroll() const -> glm::vec2 {
	return _scroll;
}

void Mouse::set_scroll(float x, float y) {
	_scroll = {x, y};
}

// NOLINTNEXTLINE
void Mouse::button_callback(GLFWwindow* window, int button, int action, int) {
	auto* ih = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	auto* mouse = ih->get_mouse();

	if (action == GLFW_PRESS) {
		mouse->set_state(static_cast<MouseButton>(button), true);
	} else if (action == GLFW_RELEASE) {
		mouse->set_state(static_cast<MouseButton>(button), false);
	}
}

void Mouse::position_callback(GLFWwindow* window, double xpos, double ypos) {
	auto* ih = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	auto* mouse = ih->get_mouse();

	mouse->set_position(static_cast<float>(xpos), static_cast<float>(ypos));
}

void Mouse::scroll_callback(
	GLFWwindow* window, double xoffset, double yoffset
) {
	auto* ih = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	auto* mouse = ih->get_mouse();

	mouse->set_scroll(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

} // namespace void_engine::input
