#include "void_engine/display/monitor/monitor_manager.hpp"

#include "void_engine/display/monitor/monitor.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <cassert>
#include <string_view>
#include <vector>

namespace void_engine::display::monitor {

std::vector<Monitor*> MonitorManager::_monitors;

void MonitorManager::init() {
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
				return m->_monitor == monitor;
			});
			delete *it;
			_monitors.erase(it);
		}
	});
}

void MonitorManager::terminate() {
	glfwSetMonitorCallback(nullptr);
	for (Monitor* monitor : _monitors) {
		delete monitor;
	}
	_monitors.clear();
}

auto MonitorManager::get(std::string_view name) -> Monitor& {
	const auto it = std::ranges::find_if(_monitors, [name](Monitor* monitor) {
		return monitor->get_name() == name;
	});
	assert(it != _monitors.end() && "Monitor does not exist");
	return **it;
}

auto MonitorManager::get_all() -> const std::vector<Monitor*>& {
	return _monitors;
}

auto MonitorManager::get_primary() -> Monitor& {
	return *_monitors[0];
}

} // namespace void_engine::display::monitor
