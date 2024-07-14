#ifndef VOID_ENGINE_DISPLAY_MONITOR_MONITOR_HPP
#define VOID_ENGINE_DISPLAY_MONITOR_MONITOR_HPP

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <vector>

struct GLFWmonitor;

namespace void_engine::display {

namespace window {
class Window;
}

namespace monitor {

struct MonitorVideoMode {
	int width;
	int height;
	int red_bits;
	int green_bits;
	int blue_bits;
	int refresh_rate;
};

class Monitor {
	friend class MonitorManager;
	friend class window::Window;

public:
	explicit Monitor(GLFWmonitor* monitor);

	void set_gamma(float gamma) const;

	[[nodiscard]] auto get_content_scale() const -> glm::vec2;
	[[nodiscard]] auto get_name() const -> const char*;
	[[nodiscard]] auto get_physical_size() const -> glm::vec2;
	[[nodiscard]] auto get_video_mode() const -> MonitorVideoMode;
	[[nodiscard]] auto get_video_modes() const -> std::vector<MonitorVideoMode>;
	[[nodiscard]] auto get_virtual_position() const -> glm::vec2;
	[[nodiscard]] auto get_work_area() const -> glm::vec4;

private:
	GLFWmonitor* _monitor;
};

} // namespace monitor

} // namespace void_engine::display

#endif // !VOID_ENGINE_DISPLAY_MONITOR_MONITOR_HPP
