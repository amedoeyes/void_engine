#include "void_engine/window/window_manager.hpp"

#include "void_engine/utils/logger.hpp"
#include "void_engine/window/window.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::window {

std::unordered_map<std::string, Window*> WindowManager::_windows;

void WindowManager::init() {
	if (!glfwInit()) {
		utils::Logger::error("Failed to initialize GLFW");
		assert(false);
	}
}

void WindowManager::terminate() {
	for (const auto& [_, window] : _windows) delete window;
	glfwTerminate();
}

auto WindowManager::create(
	const std::string& name, const std::string_view title, int width, int height
) -> Window* {
	auto* window = new Window(title, width, height);
	_windows[name] = window;
	return window;
}

auto WindowManager::get(const std::string& name) -> Window* {
	auto it = _windows.find(name);
	if (it == _windows.end())
		throw std::runtime_error("Window not found: " + name);
	return it->second;
}

void WindowManager::destroy(const std::string& name) {
	auto it = _windows.find(name);
	if (it == _windows.end())
		throw std::runtime_error("Window not found: " + name);
	delete it->second;
	_windows.erase(it);
}

void WindowManager::poll_events() {
	for (auto& [_, window] : _windows) window->get_input_handler()->update();
	glfwPollEvents();
}

} // namespace void_engine::window
