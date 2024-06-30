#ifndef VOID_ENGINE_WINDOW_EVENTS_WINDOW_SIZE_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_WINDOW_SIZE_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::window::events {

struct WindowSizeEvent {
	glm::vec2 size;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_WINDOW_SIZE_EVENT_HPP
