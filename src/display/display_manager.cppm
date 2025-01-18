module;

#include "void_engine/display/monitor/monitor_manager.hpp"
#include "void_engine/utility/logger.hpp"

#include <GLFW/glfw3.h>

export module void_engine.display.display_manager;

import std;
import glm;
import void_engine.window.window_manager;

export namespace void_engine::display {

class DisplayManager {
public:
	DisplayManager(const DisplayManager&) = default;
	DisplayManager(DisplayManager&&) = default;
	auto operator=(const DisplayManager&) -> DisplayManager& = default;
	auto operator=(DisplayManager&&) -> DisplayManager& = default;
	DisplayManager() {
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

	~DisplayManager() {
		delete _window_manager;
		delete _monitor_manager;
		--_instance_count;
		if (_instance_count == 0) {
			glfwSetErrorCallback(nullptr);
			glfwTerminate();
		}
	}

	auto windows() -> window::WindowManager& {
		return *_window_manager;
	}

	auto monitors() -> monitor::MonitorManager& {
		return *_monitor_manager;
	}

private:
	static inline unsigned int _instance_count;
	window::WindowManager* _window_manager;
	monitor::MonitorManager* _monitor_manager;
};

} // namespace void_engine::display
