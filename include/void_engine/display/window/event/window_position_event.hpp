#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENT_WINDOW_POSITION_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENT_WINDOW_POSITION_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::display::window::event {

struct WindowPositionEvent {
	glm::vec2 position;
};

} // namespace void_engine::display::window::event

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENT_WINDOW_POSITION_EVENT_HPP
