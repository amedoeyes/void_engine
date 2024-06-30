#ifndef VOID_ENGINE_WINDOW_EVENTS_FRAMEBUFFER_SIZE_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_FRAMEBUFFER_SIZE_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::window::events {

struct FramebufferSizeEvent {
	glm::vec2 size;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_FRAMEBUFFER_SIZE_EVENT_HPP
