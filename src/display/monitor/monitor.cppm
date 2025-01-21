module;

#include "void_engine/display/monitor/video_mode.hpp"

#include <GLFW/glfw3.h>

export module void_engine.display.monitor.monitor;

import std;
import glm;

export namespace void_engine::display::monitor {

class Monitor {
public:
	explicit Monitor(GLFWmonitor* monitor) : _monitor(monitor) {
		_name = glfwGetMonitorName(_monitor);
		int physical_width = 0;
		int physical_height = 0;
		glfwGetMonitorPhysicalSize(_monitor, &physical_width, &physical_height);
		_physical_size = {physical_width, physical_height};
		int position_x = 0;
		int position_y = 0;
		glfwGetMonitorPos(_monitor, &position_x, &position_y);
		_virtual_position = {position_x, position_y};
		float content_scale_x = 0.0f;
		float content_scale_y = 0.0f;
		glfwGetMonitorContentScale(_monitor, &content_scale_x, &content_scale_y);
		_content_scale = {content_scale_x, content_scale_y};
		const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
		_video_mode = {
			.size = {mode->width, mode->height},
			.color_bits = {mode->redBits, mode->greenBits, mode->blueBits},
			.refresh_rate = mode->refreshRate,
		};
		int count = 0;
		const GLFWvidmode* modes = glfwGetVideoModes(_monitor, &count);
		_video_modes.reserve(count);
		for (int i = 0; i < count; i++) {
			_video_modes.push_back(VideoMode{
				.size = {modes[i].width, modes[i].height},
				.color_bits = {modes[i].redBits, modes[i].greenBits, modes[i].blueBits},
				.refresh_rate = modes[i].refreshRate,
			});
		}
	}

	void set_gamma(float gamma) const {
		glfwSetGamma(_monitor, gamma);
	}

	[[nodiscard]] auto get_content_scale() const -> const glm::vec2& {
		return _content_scale;
	}

	[[nodiscard]] auto get_name() const -> std::string_view {
		return _name;
	}

	[[nodiscard]] auto get_physical_size() const -> const glm::uvec2& {
		return _physical_size;
	}

	[[nodiscard]] auto get_video_mode() const -> const VideoMode& {
		return _video_mode;
	}

	[[nodiscard]] auto get_video_modes() const -> std::span<const VideoMode> {
		return _video_modes;
	}

	[[nodiscard]] auto get_virtual_position() const -> const glm::uvec2& {
		return _virtual_position;
	}

	[[nodiscard]] auto get_work_area() const -> std::pair<glm::uvec2, glm::uvec2> {
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		glfwGetMonitorWorkarea(_monitor, &x, &y, &width, &height);
		return {{x, y}, {width, height}};
	}

	[[nodiscard]] auto raw() const -> GLFWmonitor* {
		return _monitor;
	}

private:
	GLFWmonitor* _monitor;
	glm::vec2 _content_scale = {0.0f, 0.0f};
	std::string _name;
	glm::uvec2 _physical_size = {0, 0};
	VideoMode _video_mode = {};
	std::vector<VideoMode> _video_modes;
	glm::uvec2 _virtual_position = {0, 0};
};

} // namespace void_engine::display::monitor
