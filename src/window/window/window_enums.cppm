module;

#include <GLFW/glfw3.h>

export module void_engine.window:window_enums;

import std;

export namespace void_engine::window {

enum class cursor_mode : std::int32_t {
	normal = GLFW_CURSOR_NORMAL,
	hidden = GLFW_CURSOR_HIDDEN,
	disabled = GLFW_CURSOR_DISABLED,
	captured = GLFW_CURSOR_CAPTURED,
};

enum class cursor_shape : std::int32_t {
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

} // namespace void_engine::window
