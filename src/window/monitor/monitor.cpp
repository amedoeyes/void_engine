module;

#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;

namespace void_engine::window {

Monitor::Monitor(GLFWmonitor* monitor) : _monitor(monitor) {}

auto Monitor::raw() const -> GLFWmonitor* {
	return _monitor;
}

void Monitor::set_gamma(float gamma) const {
	glfwSetGamma(_monitor, gamma);
}

auto Monitor::get_content_scale() const -> glm::vec2 {
	auto scale = glm::vec2();
	glfwGetMonitorContentScale(_monitor, &scale.x, &scale.y);
	return scale;
}

auto Monitor::get_name() const -> std::string_view {
	return glfwGetMonitorName(_monitor);
}

auto Monitor::get_physical_size() const -> glm::ivec2 {
	auto size = glm::ivec2();
	glfwGetMonitorPhysicalSize(_monitor, &size.x, &size.y);
	return size;
}

auto Monitor::get_video_mode() const -> VideoMode {
	const auto* mode = glfwGetVideoMode(_monitor);
	return {
		.size = {mode->width, mode->height},
		.color_bits = {mode->redBits, mode->greenBits, mode->blueBits},
		.refresh_rate = mode->refreshRate,
	};
}

auto Monitor::get_video_modes() const -> std::vector<VideoMode> {
	int count = 0;
	const GLFWvidmode* modes = glfwGetVideoModes(_monitor, &count);
	auto video_modes = std::vector<VideoMode>();
	video_modes.reserve(count);
	for (auto i = 0; i < count; ++i) {
		video_modes.emplace_back(VideoMode{
			.size = {modes[i].width, modes[i].height},
			.color_bits = {modes[i].redBits, modes[i].greenBits, modes[i].blueBits},
			.refresh_rate = modes[i].refreshRate,
		});
	}
	return video_modes;
}

auto Monitor::get_virtual_position() const -> glm::ivec2 {
	auto pos = glm::ivec2();
	glfwGetMonitorPos(_monitor, &pos.x, &pos.y);
	return pos;
}

auto Monitor::get_work_area() const -> std::pair<glm::ivec2, glm::ivec2> {
	auto pos = glm::ivec2();
	auto size = glm::ivec2();
	glfwGetMonitorWorkarea(_monitor, &pos.x, &pos.y, &size.x, &size.y);
	return {pos, size};
}

} // namespace void_engine::window
