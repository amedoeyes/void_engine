module;

#include <GLFW/glfw3.h>

export module void_engine.window:monitor;

import :video_mode;

import glm;
import std;

export namespace void_engine::window {

class monitor {
public:
	explicit monitor(GLFWmonitor* monitor);

	void set_gamma(float gamma) const;

	[[nodiscard]]
	auto get_content_scale() const -> glm::vec2;

	[[nodiscard]]
	auto get_name() const -> std::string_view;

	[[nodiscard]]
	auto get_physical_size() const -> glm::ivec2;

	[[nodiscard]]
	auto get_video_mode() const -> video_mode;

	[[nodiscard]]
	auto get_video_modes() const -> std::vector<video_mode>;

	[[nodiscard]]
	auto get_virtual_position() const -> glm::ivec2;

	[[nodiscard]]
	auto get_work_area() const -> std::pair<glm::ivec2, glm::ivec2>;

	[[nodiscard]]
	auto raw() const -> GLFWmonitor*;

private:
	GLFWmonitor* monitor_;
};

} // namespace void_engine::window
