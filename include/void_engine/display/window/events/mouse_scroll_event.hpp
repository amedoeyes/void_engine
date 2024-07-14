#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENTS_MOUSE_SCROLL_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENTS_MOUSE_SCROLL_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::display::window::events {

struct MouseScrollEvent {
	glm::vec2 offset;
};

} // namespace void_engine::display::window::events

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENTS_MOUSE_SCROLL_EVENT_HPP
