#ifndef VOID_ENGINE_WINDOW_EVENTS_WINDOW_POSITION_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_WINDOW_POSITION_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::window::events {

struct WindowPositionEvent {
	glm::vec2 position;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_WINDOW_POSITION_EVENT_HPP
