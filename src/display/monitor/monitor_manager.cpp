#include "void_engine/display/monitor/monitor_manager.hpp"

#include "void_engine/display/monitor/monitor.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <string_view>
#include <vector>

namespace void_engine::display::monitor {

std::vector<Monitor*> MonitorManager::_monitor;

void MonitorManager::init() {
	int count = 0;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	_monitor.reserve(count);
	for (int i = 0; i < count; i++) {
		_monitor.push_back(new Monitor(monitors[i]));
	}
	glfwSetMonitorCallback([](GLFWmonitor* monitor, int event) {
		if (event == GLFW_CONNECTED) {
			if (glfwGetPrimaryMonitor() == monitor) {
				_monitor.insert(_monitor.begin(), new Monitor(monitor));
			} else {
				_monitor.push_back(new Monitor(monitor));
			}
		} else if (event == GLFW_DISCONNECTED) {
			const auto it = std::find_if(_monitor.begin(), _monitor.end(), [monitor](Monitor* m) {
				return m->_monitor == monitor;
			});
			delete *it;
			_monitor.erase(it);
		}
	});
}

void MonitorManager::terminate() {
	glfwSetMonitorCallback(nullptr);
	for (Monitor* monitor : _monitor) {
		delete monitor;
	}
	_monitor.clear();
}

auto MonitorManager::get(std::string_view name) -> Monitor& {
	const auto it = std::find_if(_monitor.begin(), _monitor.end(), [name](Monitor* monitor) {
		return monitor->get_name() == name;
	});
	return **it;
}

auto MonitorManager::get_all() -> const std::vector<Monitor*>& {
	return _monitor;
}

auto MonitorManager::get_primary() -> Monitor& {
	return *_monitor[0];
}

} // namespace void_engine::display::monitor
