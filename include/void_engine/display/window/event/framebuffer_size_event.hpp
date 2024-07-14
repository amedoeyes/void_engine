#ifndef VOID_ENGINE_DISPLAY_WINDOW_EVENT_FRAMEBUFFER_SIZE_EVENT_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_EVENT_FRAMEBUFFER_SIZE_EVENT_HPP

#include "glm/ext/vector_float2.hpp"

namespace void_engine::display::window::event {

struct FramebufferSizeEvent {
	glm::vec2 size;
};

} // namespace void_engine::display::window::event

#endif // !VOID_ENGINE_DISPLAY_WINDOW_EVENT_FRAMEBUFFER_SIZE_EVENT_HPP
