#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_KEY_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_KEY_EVENT_HPP

namespace void_engine::display::window::event {

struct KeyboardKeyEvent {
	int key;
	int scancode;
	int action;
	int mods;
};

} // namespace void_engine::display::window::event

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_KEY_EVENT_HPP
