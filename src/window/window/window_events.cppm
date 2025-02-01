export module void_engine.window:window_events;

import :input.keyboard_enums;
import :input.mouse_enums;

import std;
import glm;
import void_engine.utility.bit_mask;

export namespace void_engine::window::event {

struct drop {
	std::vector<std::filesystem::path> paths;
};

struct framebuffer_size {
	glm::vec2 size;
};

struct keyboard_char {
	unsigned int codepoint;
};

struct keyboard_char_mods {
	unsigned int codepoint;
	int mods;
};

struct keyboard_key {
	input::keyboard::Key key;
	std::int32_t scancode;
	input::keyboard::KeyAction action;
	utility::BitMask<input::keyboard::KeyMod> mods;
};

struct mouse_button {
	input::mouse::Button button;
	input::mouse::ButtonAction action;
	utility::BitMask<input::keyboard::KeyMod> mods;
};

struct mouse_enter {
	bool entered;
};

struct mouse_position {
	glm::vec2 position;
};

struct mouse_scroll {
	glm::vec2 offset;
};

struct window_close {};

struct window_content_scale {
	glm::vec2 scale;
};

struct window_focus {
	bool focused;
};

struct window_iconify {
	bool iconified;
};

struct window_maximize {
	bool maximized;
};

struct window_position {
	glm::vec2 position;
};

struct window_refresh {};

struct window_size {
	glm::vec2 size;
};

} // namespace void_engine::window::event
