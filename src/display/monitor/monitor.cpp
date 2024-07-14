#include "void_engine/display/monitor/monitor.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <vector>

namespace void_engine::display::monitor {

Monitor::Monitor(GLFWmonitor* monitor) : _monitor(monitor) {
}

void Monitor::set_gamma(float gamma) const {
	glfwSetGamma(_monitor, gamma);
}

auto Monitor::get_content_scale() const -> glm::vec2 {
	float x = 0.0f;
	float y = 0.0f;
	glfwGetMonitorContentScale(_monitor, &x, &y);
	return {x, y};
}

auto Monitor::get_name() const -> const char* {
	return glfwGetMonitorName(_monitor);
}

auto Monitor::get_physical_size() const -> glm::vec2 {
	int width = 0;
	int height = 0;
	glfwGetMonitorPhysicalSize(_monitor, &width, &height);
	return {width, height};
}

auto Monitor::get_video_mode() const -> MonitorVideoMode {
	const GLFWvidmode mode = *glfwGetVideoMode(_monitor);
	return {mode.width, mode.height, mode.redBits, mode.greenBits, mode.blueBits, mode.refreshRate};
}

auto Monitor::get_video_modes() const -> std::vector<MonitorVideoMode> {
	int count = 0;
	const GLFWvidmode* modes = glfwGetVideoModes(_monitor, &count);
	std::vector<MonitorVideoMode> result(count);
	for (int i = 0; i < count; i++) {
		result[i].width = modes[i].width;
		result[i].height = modes[i].height;
		result[i].red_bits = modes[i].redBits;
		result[i].green_bits = modes[i].greenBits;
		result[i].blue_bits = modes[i].blueBits;
		result[i].refresh_rate = modes[i].refreshRate;
	}
	return result;
}

auto Monitor::get_virtual_position() const -> glm::vec2 {
	int x = 0;
	int y = 0;
	glfwGetMonitorPos(_monitor, &x, &y);
	return {x, y};
}

auto Monitor::get_work_area() const -> glm::vec4 {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	glfwGetMonitorWorkarea(_monitor, &x, &y, &width, &height);
	return {x, y, width, height};
}

} // namespace void_engine::display::monitor
