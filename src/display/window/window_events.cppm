export module void_engine.display:window.window_events;

import :input.keyboard.enums;
import :input.mouse.enums;

import std;
import glm;
import void_engine.utility.bit_mask;

export namespace void_engine::display::window::event {

struct DropEvent {
	std::vector<std::filesystem::path> paths;
};

struct FramebufferSizeEvent {
	glm::vec2 size;
};

struct KeyboardCharEvent {
	unsigned int codepoint;
};

struct KeyboardCharModsEvent {
	unsigned int codepoint;
	int mods;
};

struct KeyboardKeyEvent {
	input::keyboard::Key key;
	int scancode;
	input::keyboard::KeyAction action;
	utility::BitMask<input::keyboard::KeyMod> mods;
};

struct MouseButtonEvent {
	input::mouse::Button button;
	input::mouse::ButtonAction action;
	utility::BitMask<input::keyboard::KeyMod> mods;
};

struct MouseEnterEvent {
	bool entered;
};

struct MousePositionEvent {
	glm::vec2 position;
};

struct MouseScrollEvent {
	glm::vec2 offset;
};

struct WindowCloseEvent {};

struct WindowContentScaleEvent {
	glm::vec2 scale;
};

struct WindowFocusEvent {
	bool focused;
};

struct WindowIconifyEvent {
	bool iconified;
};

struct WindowMaximizeEvent {
	bool maximized;
};

struct WindowPositionEvent {
	glm::vec2 position;
};

struct WindowRefreshEvent {};

struct WindowSizeEvent {
	glm::vec2 size;
};

} // namespace void_engine::display::window::event
