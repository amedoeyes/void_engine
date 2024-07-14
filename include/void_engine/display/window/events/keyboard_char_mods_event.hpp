#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENTS_KEYBOARD_CHAR_MODS_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENTS_KEYBOARD_CHAR_MODS_EVENT_HPP

namespace void_engine::display::window::events {

struct KeyboardCharModsEvent {
	unsigned int codepoint;
	int mods;
};

} // namespace void_engine::display::window::events

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENTS_KEYBOARD_CHAR_MODS_EVENT_HPP
