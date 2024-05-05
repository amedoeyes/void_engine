#include "void_engine/window/window_manager.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cassert>

namespace void_engine::window {

std::vector<Window*> WindowManager::_windows;

void WindowManager::init() {
	if (!glfwInit()) assert(false && "GLFW Error: Failed to initialize GLFW");
}

void WindowManager::terminate() {
	for (auto window : _windows) delete window;
	glfwTerminate();
}

Window* WindowManager::create(
	const char* title, const int& width, const int& height
) {
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

}  // namespace void_engine::window
