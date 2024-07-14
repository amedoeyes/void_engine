#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENTS_KEYBOARD_KEY_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENTS_KEYBOARD_KEY_EVENT_HPP

namespace void_engine::display::window::events {

struct KeyboardKeyEvent {
	int key;
	int scancode;
	int action;
	int mods;
};

} // namespace void_engine::display::window::events

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENTS_KEYBOARD_KEY_EVENT_HPP
