module;

#include <GLFW/glfw3.h>
#include <cassert>

module void_engine.display;
import :display_manager;

import :window.window_manager;
import :monitor.monitor_manager;

import std;
import glm;
import void_engine.utility.logger;

namespace void_engine::display {

DisplayManager::DisplayManager() {
	if (_instance_count == 0) {
		const int result = glfwInit();
		assert(result != 0 && "Failed to initialize GLFW");
#ifdef DEBUG
		glfwSetErrorCallback([](int, const char* description) {
			utility::logger::error("GLFW: {}", description);
		});
#endif
	}
	++_instance_count;
	_window_manager = new window::WindowManager();
	_monitor_manager = new monitor::MonitorManager();
}

DisplayManager::~DisplayManager() {
	delete _window_manager;
	delete _monitor_manager;
	--_instance_count;
	if (_instance_count == 0) {
		glfwSetErrorCallback(nullptr);
		glfwTerminate();
	}
}

auto DisplayManager::windows() -> window::WindowManager& {
	return *_window_manager;
}

auto DisplayManager::monitors() -> monitor::MonitorManager& {
	return *_monitor_manager;
}

} // namespace void_engine::display
