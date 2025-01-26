module;

#include <GLFW/glfw3.h>
#include <cassert>

module void_engine.display;

import :monitor.monitor;
import :monitor.monitor_manager;

import std;
import glm;

namespace void_engine::display::monitor {

MonitorManager::MonitorManager() {
	if (_instance_count == 0) {
		int count = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		_monitors.reserve(count);
		for (int i = 0; i < count; i++) {
			_monitors.push_back(new Monitor(monitors[i]));
		}
		glfwSetMonitorCallback([](GLFWmonitor* monitor, int event) {
			if (event == GLFW_CONNECTED) {
				_monitors.push_back(new Monitor(monitor));
			} else if (event == GLFW_DISCONNECTED) {
				const auto it = std::ranges::find_if(_monitors, [monitor](Monitor* m) {
					return m->raw() == monitor;
				});
				delete *it;
				_monitors.erase(it);
			}
		});
	}
	++_instance_count;
}

MonitorManager::~MonitorManager() {
	--_instance_count;
	if (_instance_count == 0) {
		glfwSetMonitorCallback(nullptr);
		for (const auto* monitor : _monitors) {
			delete monitor;
		}
	}
}

auto MonitorManager::get(std::string_view name) -> Monitor& {
	const auto it = std::ranges::find_if(_monitors, [name](Monitor* monitor) {
		return monitor->get_name() == name;
	});
	assert(it != _monitors.end() && "Monitor does not exist");
	return **it;
}

auto MonitorManager::get_all() -> std::span<Monitor*> {
	return _monitors;
}

auto MonitorManager::get_primary() -> Monitor& {
	return *_monitors[0];
}

} // namespace void_engine::display::monitor
