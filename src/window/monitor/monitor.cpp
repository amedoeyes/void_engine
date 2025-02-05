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

auto monitor::content_scale() const -> glm::vec2 {
	auto scale = glm::vec2{};
	glfwGetMonitorContentScale(monitor_, &scale.x, &scale.y);
	return scale;
}

auto monitor::name() const -> std::string_view {
	return glfwGetMonitorName(monitor_);
}

auto monitor::physical_size() const -> glm::ivec2 {
	auto size = glm::ivec2{};
	glfwGetMonitorPhysicalSize(monitor_, &size.x, &size.y);
	return size;
}

auto monitor::current_video_mode() const -> video_mode {
	const auto* mode = glfwGetVideoMode(monitor_);
	return {
		.size = {mode->width, mode->height},
		.color_bits = {mode->redBits, mode->greenBits, mode->blueBits},
		.refresh_rate = mode->refreshRate,
	};
}

auto monitor::video_modes() const -> std::vector<video_mode> {
	int count = 0;
	const GLFWvidmode* modes = glfwGetVideoModes(monitor_, &count);
	return std::span(modes, count) //
	     | std::views::transform([](const auto mode) {
					 return video_mode{
						 .size = {mode.width, mode.height},
						 .color_bits = {mode.redBits, mode.greenBits, mode.blueBits},
						 .refresh_rate = mode.refreshRate,
					 };
				 })
	     | std::ranges::to<std::vector>();
}

auto monitor::virtual_position() const -> glm::ivec2 {
	auto pos = glm::ivec2{};
	glfwGetMonitorPos(monitor_, &pos.x, &pos.y);
	return pos;
}

auto monitor::work_area() const -> std::pair<glm::ivec2, glm::ivec2> {
	auto pos = glm::ivec2{};
	auto size = glm::ivec2{};
	glfwGetMonitorWorkarea(monitor_, &pos.x, &pos.y, &size.x, &size.y);
	return {pos, size};
}

auto monitor::raw() const -> GLFWmonitor* {
	return monitor_;
}

} // namespace void_engine::window
