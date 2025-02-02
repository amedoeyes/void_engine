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

enum class mouse_mode : std::int32_t {
	normal = GLFW_CURSOR_NORMAL,
	hidden = GLFW_CURSOR_HIDDEN,
	disabled = GLFW_CURSOR_DISABLED,
	captured = GLFW_CURSOR_CAPTURED,
};

enum class mouse_shape : std::int32_t {
	arrow = GLFW_ARROW_CURSOR,
	ibeam = GLFW_IBEAM_CURSOR,
	crosshair = GLFW_CROSSHAIR_CURSOR,
	pointing_hand = GLFW_POINTING_HAND_CURSOR,
	resize_ew = GLFW_RESIZE_EW_CURSOR,
	resize_ns = GLFW_RESIZE_NS_CURSOR,
	resize_nwse = GLFW_RESIZE_NWSE_CURSOR,
	resize_nesw = GLFW_RESIZE_NESW_CURSOR,
	resize_all = GLFW_RESIZE_ALL_CURSOR,
	not_allowed = GLFW_NOT_ALLOWED_CURSOR,
};

} // namespace void_engine::window::input
