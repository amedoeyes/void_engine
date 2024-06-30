#ifndef VOID_ENGINE_WINDOW_EVENTS_MOUSE_BUTTON_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_MOUSE_BUTTON_EVENT_HPP

namespace void_engine::window::events {

struct MouseButtonEvent {
	int button;
	int action;
	int mods;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_MOUSE_BUTTON_EVENT_HPP
