#include "void_engine/display/display_manager.hpp"

#include "void_engine/display/monitor/monitor_manager.hpp"
#include "void_engine/display/window/window_manager.hpp"
#include "void_engine/utility/logger.hpp"

#include <GLFW/glfw3.h>
#include <cassert>

namespace void_engine::display {

void DisplayManager::init() {
	if (glfwInit() == 0) {
		assert(false && "Failed to initialize GLFW");
	}
	glfwSetErrorCallback([](int, const char* description) {
		utility::Logger::error("GLFW: {}", description);
	});
	monitor::MonitorManager::init();
}

void DisplayManager::terminate() {
	window::WindowManager::terminate();
	monitor::MonitorManager::terminate();
	glfwSetErrorCallback(nullptr);
	glfwTerminate();
}

} // namespace void_engine::display
