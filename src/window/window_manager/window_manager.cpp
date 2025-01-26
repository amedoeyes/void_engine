module;

#include <GLFW/glfw3.h>
#include <cassert>

module void_engine.window;

import std;
import glm;
import void_engine.utility.logger;

namespace void_engine::window {

WindowManager::WindowManager() {
	if (_instance_count == 0) {
		const auto result = glfwInit();
		assert(result != 0 && "Failed to initialize GLFW");
		auto monitor_count = 0;
		auto* monitors = glfwGetMonitors(&monitor_count);
		_monitors.reserve(monitor_count);
		for (auto i = 0; i < monitor_count; ++i) {
			_monitors.emplace_back(monitors[i]);
		}
		glfwSetMonitorCallback([](GLFWmonitor*, int) {
			_monitors.clear();
			auto monitor_count = 0;
			auto* monitors = glfwGetMonitors(&monitor_count);
			_monitors.reserve(monitor_count);
			for (auto i = 0; i < monitor_count; ++i) {
				_monitors.emplace_back(monitors[i]);
			}
		});
#ifdef DEBUG
		glfwSetErrorCallback([](int, const char* description) {
			utility::logger::error("GLFW: {}", description);
		});
#endif
	}
	++_instance_count;
}

WindowManager::~WindowManager() {
	--_instance_count;
	if (_instance_count == 0) {
		glfwSetErrorCallback(nullptr);
		glfwSetMonitorCallback(nullptr);
		glfwTerminate();
	}
}

auto WindowManager::create(
	std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Window& share,
	const Hints& hints
) -> Window& {
	_windows.emplace_back(title, size, monitor, share, hints);
	return _windows.back();
}

auto WindowManager::create(
	std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints
) -> Window& {
	_windows.emplace_back(title, size, monitor, hints);
	return _windows.back();
}

auto WindowManager::create(
	std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints
) -> Window& {
	_windows.emplace_back(title, size, share, hints);
	return _windows.back();
}

auto WindowManager::create(std::string_view title, const glm::ivec2& size, const Hints& hints)
	-> Window& {
	_windows.emplace_back(title, size, hints);
	return _windows.back();
}

void WindowManager::destroy(const Window& window) {
	const auto it = std::ranges::find_if(_windows, [&](const auto& w) {
		return w.raw() == window.raw();
	});
	_windows.erase(it);
}

void WindowManager::poll_events() {
	glfwPollEvents();
	for (auto& window : _windows) {
		window.get_inputs().update();
	}
}

auto WindowManager::get_windows() -> std::span<Window> {
	return _windows;
}

auto WindowManager::get_monitor(std::string_view name) -> Monitor& {
	const auto it = std::ranges::find_if(_monitors, [&](const auto& m) {
		return m.get_name() == name;
	});
	assert(it != _monitors.end() && "Monitor does not exist");
	return *it;
}

auto WindowManager::get_monitors() -> std::span<Monitor> {
	return _monitors;
}

auto WindowManager::get_primary_monitor() -> Monitor& {
	return _monitors[0];
}

} // namespace void_engine::window
