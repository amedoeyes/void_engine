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
	auto content_scale() const -> glm::vec2;

	[[nodiscard]]
	auto name() const -> std::string_view;

	[[nodiscard]]
	auto physical_size() const -> glm::ivec2;

	[[nodiscard]]
	auto current_video_mode() const -> video_mode;

	[[nodiscard]]
	auto video_modes() const -> std::vector<video_mode>;

	[[nodiscard]]
	auto virtual_position() const -> glm::ivec2;

	[[nodiscard]]
	auto work_area() const -> std::pair<glm::ivec2, glm::ivec2>;

	[[nodiscard]]
	auto raw() const -> GLFWmonitor*;

private:
	GLFWmonitor* monitor_;
};

} // namespace void_engine::window
