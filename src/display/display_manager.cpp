#include "void_engine/display/display_manager.hpp"

#include "void_engine/display/monitor/monitor_manager.hpp"
#include "void_engine/display/window/window_manager.hpp"
#include "void_engine/utility/logger.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/ext/vector_int2.hpp>
#include <string_view>

namespace void_engine::display {

DisplayManager::DisplayManager() {
	if (_instance_count == 0) {
		const int result = glfwInit();
		assert(result != 0 && "Failed to initialize GLFW");
		glfwSetErrorCallback([](int, const char* description) {
			utility::logger::error("GLFW: {}", description);
		});
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
