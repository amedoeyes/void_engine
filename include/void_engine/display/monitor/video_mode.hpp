#ifndef VOID_ENGINE_DISPLAY_MONITOR_VIDEO_MODE_HPP
#define VOID_ENGINE_DISPLAY_MONITOR_VIDEO_MODE_HPP

#include <glm/ext/vector_uint2.hpp>
#include <glm/ext/vector_uint3.hpp>

namespace void_engine::display::monitor {

struct VideoMode {
	glm::uvec2 size;
	glm::uvec3 color_bits;
	unsigned int refresh_rate;
};

} // namespace void_engine::display::monitor

#endif // !VOID_ENGINE_DISPLAY_MONITOR_VIDEO_MODE_HPP
