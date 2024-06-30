#ifndef VOID_ENGINE_WINDOW_EVENTS_MOUSE_SCROLL_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_MOUSE_SCROLL_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::window::events {

struct MouseScrollEvent {
	glm::vec2 offset;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_MOUSE_SCROLL_EVENT_HPP
