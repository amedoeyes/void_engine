module;

#include <GLFW/glfw3.h>

export module void_engine.window:monitor;

import :video_mode;

import std;
import glm;

export namespace void_engine::window {

class Monitor {
public:
	Monitor(const Monitor&) = default;
	Monitor(Monitor&&) = default;
	auto operator=(const Monitor&) -> Monitor& = default;
	auto operator=(Monitor&&) -> Monitor& = default;
	explicit Monitor(GLFWmonitor* monitor);
	~Monitor() = default;

	[[nodiscard]]
	auto raw() const -> GLFWmonitor*;

	void set_gamma(float gamma) const;

	[[nodiscard]]
	auto get_content_scale() const -> glm::vec2;
	[[nodiscard]]
	auto get_name() const -> std::string_view;
	[[nodiscard]]
	auto get_physical_size() const -> glm::ivec2;
	[[nodiscard]]
	auto get_video_mode() const -> VideoMode;
	[[nodiscard]]
	auto get_video_modes() const -> std::vector<VideoMode>;
	[[nodiscard]]
	auto get_virtual_position() const -> glm::ivec2;
	[[nodiscard]]
	auto get_work_area() const -> std::pair<glm::ivec2, glm::ivec2>;

private:
	GLFWmonitor* _monitor;
};

} // namespace void_engine::window
