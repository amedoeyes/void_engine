#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENTS_MOUSE_BUTTON_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENTS_MOUSE_BUTTON_EVENT_HPP

namespace void_engine::display::window::events {

struct MouseButtonEvent {
	int button;
	int action;
	int mods;
};

} // namespace void_engine::display::window::events

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENTS_MOUSE_BUTTON_EVENT_HPP
