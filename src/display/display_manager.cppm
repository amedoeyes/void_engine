module;

#include <GLFW/glfw3.h>
#include <cassert>

export module void_engine.display:display_manager;

import :window.window_manager;
import :monitor.monitor_manager;

export namespace void_engine::display {

class DisplayManager {
public:
	DisplayManager(const DisplayManager&) = default;
	DisplayManager(DisplayManager&&) = default;
	auto operator=(const DisplayManager&) -> DisplayManager& = default;
	auto operator=(DisplayManager&&) -> DisplayManager& = default;
	DisplayManager();
	~DisplayManager();

	auto windows() -> window::WindowManager&;
	auto monitors() -> monitor::MonitorManager&;

private:
	static inline unsigned int _instance_count;
	window::WindowManager* _window_manager;
	monitor::MonitorManager* _monitor_manager;
};

} // namespace void_engine::display
