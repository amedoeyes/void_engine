#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_KEY_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_KEY_EVENT_HPP

#include "void_engine/display/window/input/keyboard/enums.hpp"
#include "void_engine/utility/bit_mask.hpp"

namespace void_engine::display::window::event {

struct KeyboardKeyEvent {
	input::keyboard::Key key;
	int scancode;
	input::keyboard::KeyAction action;
	utility::BitMask<input::keyboard::KeyMod> mods;
};

} // namespace void_engine::display::window::event

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_KEY_EVENT_HPP
