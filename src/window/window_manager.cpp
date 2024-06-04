#include "void_engine/window/window_manager.hpp"

#include "void_engine/logger.hpp"

#include <GLFW/glfw3.h>
#include <cassert>

namespace void_engine::window {

std::vector<Window*> WindowManager::_windows;

void WindowManager::init() {
	if (!glfwInit()) {
		Logger::error("Failed to initialize GLFW");
		assert(false);
	}
}

void WindowManager::terminate() {
	for (auto* window : _windows) delete window;
	glfwTerminate();
}

auto WindowManager::create(const char* title, int width, int height)
	-> Window* {
	_windows.emplace_back(new Window(title, width, height));
	return _windows.back();
}

void WindowManager::destroy(Window* window) {
	auto it = std::find(_windows.begin(), _windows.end(), window);
	if (it != _windows.end()) {
		delete *it;
		_windows.erase(it);
	}
}

void WindowManager::poll_events() {
	for (auto* window : _windows) window->get_input_handler()->update();
	glfwPollEvents();
}

} // namespace void_engine::window
