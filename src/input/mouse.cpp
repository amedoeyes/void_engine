#include "void_engine/input/mouse.hpp"

#include <cstdio>

#include "void_engine/input/input_handler.hpp"

namespace void_engine::input {

void Mouse::update() {
	_prev_states = _states;
}

bool Mouse::is_button_down(Button button) const {
	return get_state(button);
}

bool Mouse::is_button_up(Button button) const {
	return !get_state(button);
}

bool Mouse::is_button_pressed(Button button) const {
	return get_state(button) && !get_prev_state(button);
}

bool Mouse::get_state(Button button) const {
	auto it = _states.find(button);
	if (it == _states.end()) return false;
	return it->second;
}

void Mouse::set_state(Button button, bool state) {
	_states[button] = state;
}

bool Mouse::get_prev_state(Button button) const {
	auto it = _prev_states.find(button);
	if (it == _prev_states.end()) return false;
	return it->second;
}

void Mouse::set_prev_state(Button button, bool state) {
	_prev_states[button] = state;
}

Mouse::Position Mouse::get_position() const {
	return _position;
}

void Mouse::set_position(float x, float y) {
	_position = {x, y};
}

Mouse::Scroll Mouse::get_scroll() const {
	return _scroll;
}

void Mouse::set_scroll(float x, float y) {
	_scroll = {x, y};
}

void Mouse::button_callback(
	GLFWwindow *window, int button, int action, [[maybe_unused]] int mods
) {
	auto ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
	auto mouse = ih->get_mouse();

	if (action == GLFW_PRESS) {
		mouse->set_state(static_cast<Mouse::Button>(button), true);
	} else if (action == GLFW_RELEASE) {
		mouse->set_state(static_cast<Mouse::Button>(button), false);
	}
}

void Mouse::position_callback(GLFWwindow *window, double xpos, double ypos) {
	auto ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
	auto mouse = ih->get_mouse();

	mouse->set_position(xpos, ypos);
}

void Mouse::scroll_callback(
	GLFWwindow *window, double xoffset, double yoffset
) {
	auto ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
	auto mouse = ih->get_mouse();

	mouse->set_scroll(xoffset, yoffset);
}

}  // namespace void_engine::input
