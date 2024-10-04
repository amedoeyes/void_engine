#ifndef VOID_ENGINE_DISPLAY_MONITOR_VIDEO_MODE_HPP
#define VOID_ENGINE_DISPLAY_MONITOR_VIDEO_MODE_HPP

#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_int3.hpp>

namespace void_engine::display::monitor {

struct VideoMode {
	glm::ivec2 size;
	glm::ivec3 color_bits;
	int refresh_rate;
};

} // namespace void_engine::display::monitor

#endif // !VOID_ENGINE_DISPLAY_MONITOR_VIDEO_MODE_HPP
