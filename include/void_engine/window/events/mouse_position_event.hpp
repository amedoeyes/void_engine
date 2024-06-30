#ifndef VOID_ENGINE_WINDOW_EVENTS_MOUSE_POSITION_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_MOUSE_POSITION_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::window::events {

struct MousePositionEvent {
	glm::vec2 position;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_MOUSE_POSITION_EVENT_HPP
