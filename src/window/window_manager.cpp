#include "void_engine/window/window_manager.hpp"

#include "void_engine/utils/logger.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::window {

std::unordered_map<std::string, Window*> WindowManager::_windows;

void WindowManager::init() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwSetErrorCallback([](int, const char* description) {
		utils::Logger::error("GLFW Error: {}", description);
	});
}

void WindowManager::terminate() {
	for (const auto& [_, window] : _windows) {
		delete window;
	}
	glfwSetErrorCallback(nullptr);
	glfwTerminate();
}

auto WindowManager::create(
	const std::string& name, const std::string_view title, const glm::vec2& size
) -> Window* {
	auto* window = new Window(title, size);
	_windows[name] = window;
	return window;
}

auto WindowManager::get(const std::string& name) -> Window* {
	const auto it = _windows.find(name);
	if (it == _windows.end()) {
		throw std::runtime_error("Window not found: " + name);
	}
	return it->second;
}

void WindowManager::destroy(const std::string& name) {
	const auto it = _windows.find(name);
	if (it == _windows.end()) {
		throw std::runtime_error("Window not found: " + name);
	}
	delete it->second;
	_windows.erase(it);
}

void WindowManager::poll_events() {
	glfwPollEvents();
	for (const auto& [_, window] : _windows) {
		window->input_handler()->update();
		window->event_handler()->poll();
	}
}

} // namespace void_engine::window
