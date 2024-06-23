#include "void_engine/input/keyboard.hpp"

#include "void_engine/input/input_handler.hpp"
#include "void_engine/window/window.hpp"

#include <GLFW/glfw3.h>

namespace void_engine::input {

void Keyboard::update() {
	_prev_states = _states;
}

auto Keyboard::is_down(KeyboardKey key) const -> bool {
	return get_state(key);
}

auto Keyboard::is_up(KeyboardKey key) const -> bool {
	return !get_state(key);
}

auto Keyboard::is_pressed(KeyboardKey key) const -> bool {
	return get_state(key) && !get_prev_state(key);
}

auto Keyboard::get_state(KeyboardKey key) const -> bool {
	auto it = _states.find(key);
	if (it == _states.end()) return false;
	return it->second;
}

void Keyboard::set_state(KeyboardKey key, bool state) {
	_states[key] = state;
}

auto Keyboard::get_prev_state(KeyboardKey key) const -> bool {
	auto it = _prev_states.find(key);
	if (it == _prev_states.end()) return false;
	return it->second;
}
void Keyboard::set_prev_state(KeyboardKey key, bool state) {
	_prev_states[key] = state;
}

void Keyboard::callback(GLFWwindow* window, int key, int, int action, int) {
	auto* win = static_cast<window::Window*>(glfwGetWindowUserPointer(window));
	auto* ih = win->get_input_handler();
	auto* kb = ih->get_keyboard();
	if (action == GLFW_PRESS) {
		kb->set_state(static_cast<KeyboardKey>(key), true);
	} else if (action == GLFW_RELEASE) {
		kb->set_state(static_cast<KeyboardKey>(key), false);
	}
}

} // namespace void_engine::input
