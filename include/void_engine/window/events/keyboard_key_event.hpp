#ifndef VOID_ENGINE_WINDOW_EVENTS_KEYBOARD_KEY_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_KEYBOARD_KEY_EVENT_HPP

namespace void_engine::window::events {

struct KeyboardKeyEvent {
	int key;
	int scancode;
	int action;
	int mods;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_KEYBOARD_KEY_EVENT_HPP
