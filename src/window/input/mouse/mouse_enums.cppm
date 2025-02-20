module;

#include <GLFW/glfw3.h>

export module void_engine.window:input.mouse_enums;

import std;

export namespace void_engine::window::input {

enum class mouse_button : std::uint8_t {
	one = GLFW_MOUSE_BUTTON_1,
	two = GLFW_MOUSE_BUTTON_2,
	three = GLFW_MOUSE_BUTTON_3,
	four = GLFW_MOUSE_BUTTON_4,
	five = GLFW_MOUSE_BUTTON_5,
	six = GLFW_MOUSE_BUTTON_6,
	seven = GLFW_MOUSE_BUTTON_7,
	eight = GLFW_MOUSE_BUTTON_8,
	last = GLFW_MOUSE_BUTTON_LAST,
	left = GLFW_MOUSE_BUTTON_LEFT,
	right = GLFW_MOUSE_BUTTON_RIGHT,
	middle = GLFW_MOUSE_BUTTON_MIDDLE,
};

enum class mouse_action : std::uint8_t {
	release = GLFW_RELEASE,
	press = GLFW_PRESS,
};

} // namespace void_engine::window::input
