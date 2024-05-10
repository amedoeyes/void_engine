#include "void_engine/input/keyboard.hpp"

#include "void_engine/input/input_handler.hpp"

namespace void_engine::input {

void Keyboard::update() {
	_prev_states = _states;
}

bool Keyboard::is_key_down(KeyboardKey key) const {
	return get_state(key);
}

bool Keyboard::is_key_up(KeyboardKey key) const {
	return !get_state(key);
}

bool Keyboard::is_key_pressed(KeyboardKey key) const {
	return get_state(key) && !get_prev_state(key);
}

bool Keyboard::get_state(KeyboardKey key) const {
	auto it = _states.find(key);
	if (it == _states.end()) return false;
	return it->second;
}

void Keyboard::set_state(KeyboardKey key, bool state) {
	_states[key] = state;
}

bool Keyboard::get_prev_state(KeyboardKey key) const {
	auto it = _prev_states.find(key);
	if (it == _prev_states.end()) return false;
	return it->second;
}
void Keyboard::set_prev_state(KeyboardKey key, bool state) {
	_prev_states[key] = state;
}

void Keyboard::callback(
	GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action,
	[[maybe_unused]] int mods
) {
	auto ih = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	auto kb = ih->get_keyboard();

	if (action == GLFW_PRESS) {
		kb->set_state(static_cast<KeyboardKey>(key), true);
	} else if (action == GLFW_RELEASE) {
		kb->set_state(static_cast<KeyboardKey>(key), false);
	}
}

}  // namespace void_engine::input
