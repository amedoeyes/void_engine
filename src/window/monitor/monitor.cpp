module;

#include <GLFW/glfw3.h>

module void_engine.window;

import glm;
import std;

namespace void_engine::window {

monitor::monitor(GLFWmonitor* monitor) : monitor_{monitor} {}

void monitor::set_gamma(float gamma) const {
	glfwSetGamma(monitor_, gamma);
}

auto monitor::get_content_scale() const -> glm::vec2 {
	auto scale = glm::vec2{};
	glfwGetMonitorContentScale(monitor_, &scale.x, &scale.y);
	return scale;
}

auto monitor::get_name() const -> std::string_view {
	return glfwGetMonitorName(monitor_);
}

auto monitor::get_physical_size() const -> glm::ivec2 {
	auto size = glm::ivec2{};
	glfwGetMonitorPhysicalSize(monitor_, &size.x, &size.y);
	return size;
}

auto monitor::get_video_mode() const -> video_mode {
	const auto* mode = glfwGetVideoMode(monitor_);
	return {
		.size = {mode->width, mode->height},
		.color_bits = {mode->redBits, mode->greenBits, mode->blueBits},
		.refresh_rate = mode->refreshRate,
	};
}

auto monitor::get_video_modes() const -> std::vector<video_mode> {
	int count = 0;
	const GLFWvidmode* modes_ptr = glfwGetVideoModes(monitor_, &count);
	auto modes = std::vector<video_mode>();
	modes.reserve(count);
	for (const auto& mode : std::span(modes_ptr, count)) {
		modes.emplace_back(video_mode{
			.size = {mode.width, mode.height},
			.color_bits = {mode.redBits, mode.greenBits, mode.blueBits},
			.refresh_rate = mode.refreshRate,
		});
	}
	return modes;
}

auto monitor::get_virtual_position() const -> glm::ivec2 {
	auto pos = glm::ivec2{};
	glfwGetMonitorPos(monitor_, &pos.x, &pos.y);
	return pos;
}

auto monitor::get_work_area() const -> std::pair<glm::ivec2, glm::ivec2> {
	auto pos = glm::ivec2{};
	auto size = glm::ivec2{};
	glfwGetMonitorWorkarea(monitor_, &pos.x, &pos.y, &size.x, &size.y);
	return {pos, size};
}

auto monitor::raw() const -> GLFWmonitor* {
	return monitor_;
}

} // namespace void_engine::window
