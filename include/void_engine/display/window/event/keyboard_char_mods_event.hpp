#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_CHAR_MODS_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_CHAR_MODS_EVENT_HPP

namespace void_engine::display::window::event {

struct KeyboardCharModsEvent {
	unsigned int codepoint;
	int mods;
};

} // namespace void_engine::display::window::event

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENT_KEYBOARD_CHAR_MODS_EVENT_HPP
