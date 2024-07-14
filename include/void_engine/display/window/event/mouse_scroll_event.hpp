#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENT_MOUSE_SCROLL_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENT_MOUSE_SCROLL_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::display::window::event {

struct MouseScrollEvent {
	glm::vec2 offset;
};

} // namespace void_engine::display::window::event

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENT_MOUSE_SCROLL_EVENT_HPP
