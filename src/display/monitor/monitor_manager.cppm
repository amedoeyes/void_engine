module;

#include <GLFW/glfw3.h>
#include <cassert>

export module void_engine.display.monitor.monitor_manager;

import std;
import void_engine.display.monitor.monitor;

export namespace void_engine::display::monitor {

class MonitorManager {
public:
	MonitorManager(const MonitorManager&) = default;
	MonitorManager(MonitorManager&&) = default;
	auto operator=(const MonitorManager&) -> MonitorManager& = default;
	auto operator=(MonitorManager&&) -> MonitorManager& = default;
	MonitorManager() {
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
			++_instance_count;
		}
	}
	~MonitorManager() {
		--_instance_count;
		if (_instance_count == 0) {
			glfwSetMonitorCallback(nullptr);
			for (const auto* monitor : _monitors) {
				delete monitor;
			}
		}
	}

	[[nodiscard]] static auto get(std::string_view name) -> Monitor& {
		const auto it = std::ranges::find_if(_monitors, [name](Monitor* monitor) {
			return monitor->get_name() == name;
		});
		assert(it != _monitors.end() && "Monitor does not exist");
		return **it;
	}

	[[nodiscard]] static auto get_all() -> std::span<Monitor*> {
		return _monitors;
	}

	[[nodiscard]] static auto get_primary() -> Monitor& {
		return *_monitors[0];
	}

private:
	static inline unsigned int _instance_count;
	static inline std::vector<Monitor*> _monitors;
};

} // namespace void_engine::display::monitor

namespace void_engine::display::monitor {} // namespace void_engine::display::monitor
