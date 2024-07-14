#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENTS_WINDOW_CONTENT_SCALE_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENTS_WINDOW_CONTENT_SCALE_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::display::window::events {

struct WindowContentScaleEvent {
	glm::vec2 scale;
};

} // namespace void_engine::display::window::events

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENTS_WINDOW_CONTENT_SCALE_EVENT_HPP
