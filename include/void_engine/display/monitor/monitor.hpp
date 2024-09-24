#ifndef VOID_ENGINE_DISPLAY_MONITOR_MONITOR_HPP
#define VOID_ENGINE_DISPLAY_MONITOR_MONITOR_HPP

#include "void_engine/display/monitor/video_mode.hpp"

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_uint2.hpp>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct GLFWmonitor;

namespace void_engine::display {

namespace window {
class Window;
}

namespace monitor {

class Monitor {
	friend class MonitorManager;
	friend class window::Window;

public:
	Monitor(const Monitor&) = default;
	Monitor(Monitor&&) = default;
	auto operator=(const Monitor&) -> Monitor& = default;
	auto operator=(Monitor&&) -> Monitor& = default;
	explicit Monitor(GLFWmonitor* monitor);
	~Monitor() = default;

	void set_gamma(float gamma) const;

	[[nodiscard]] auto get_content_scale() const -> const glm::vec2&;
	[[nodiscard]] auto get_name() const -> std::string_view;
	[[nodiscard]] auto get_physical_size() const -> const glm::uvec2&;
	[[nodiscard]] auto get_video_mode() const -> const VideoMode&;
	[[nodiscard]] auto get_video_modes() const -> std::span<const VideoMode>;
	[[nodiscard]] auto get_virtual_position() const -> const glm::uvec2&;
	[[nodiscard]] auto get_work_area() const -> std::pair<glm::uvec2, glm::uvec2>;

private:
	GLFWmonitor* _monitor;
	glm::vec2 _content_scale = {0.0f, 0.0f};
	std::string _name;
	glm::uvec2 _physical_size = {0, 0};
	VideoMode _video_mode = {};
	std::vector<VideoMode> _video_modes;
	glm::uvec2 _virtual_position = {0, 0};
};

} // namespace monitor

} // namespace void_engine::display

#endif // !VOID_ENGINE_DISPLAY_MONITOR_MONITOR_HPP
