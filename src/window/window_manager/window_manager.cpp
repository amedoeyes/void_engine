module;

#include <cassert>
#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;
import void_engine.utility.logger;

namespace void_engine::window {

window_manager::window_manager() {
	if (++instance_count_ == 1) {
		const auto result = glfwInit();
		assert(result != 0 && "Failed to initialize GLFW");
#ifdef DEBUG
		glfwSetErrorCallback([](int code, const char* description) {
			utility::logger::error("GLFW[{}]: {}", code, description);
		});
#endif
	}
}

window_manager::~window_manager() {
	windows_.clear();
	if (--instance_count_ == 0) glfwTerminate();
}

auto window_manager::create(
	std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Window& share, const Hints& hints
) -> Window& {
	return *windows_.emplace_back(std::make_unique<Window>(title, size, monitor, share, hints));
}

auto window_manager::create(std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints)
	-> Window& {
	return *windows_.emplace_back(std::make_unique<Window>(title, size, monitor, hints));
}

auto window_manager::create(std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints)
	-> Window& {
	return *windows_.emplace_back(std::make_unique<Window>(title, size, share, hints));
}

auto window_manager::create(std::string_view title, const glm::ivec2& size, const Hints& hints) -> Window& {
	return *windows_.emplace_back(std::make_unique<Window>(title, size, hints));
}

auto window_manager::destroy(const Window& window) -> void {
	windows_.erase(std::ranges::find_if(windows_, [&](const auto& w) { return w->raw() == window.raw(); }));
}

auto window_manager::poll_events() -> void {
	glfwPollEvents();
	for (auto& window : windows_) {
		window->get_inputs().update();
		window->get_events().poll();
	}
}

auto window_manager::monitors() -> std::vector<Monitor> {
	auto count = 0;
	auto* monitors = glfwGetMonitors(&count);
	return std::span(monitors, count) //
	     | std::views::transform([](auto* m) { return Monitor{m}; }) //
	     | std::ranges::to<std::vector>();
}

auto window_manager::primary_monitor() -> std::optional<Monitor> {
	auto* monitor_ptr = glfwGetPrimaryMonitor();
	if (monitor_ptr == nullptr) return std::nullopt;
	return Monitor(monitor_ptr);
}

} // namespace void_engine::window
