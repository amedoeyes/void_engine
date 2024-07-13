#include "void_engine/window/window_manager.hpp"

#include "void_engine/utils/logger.hpp"
#include "void_engine/window/window.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::window {

std::unordered_map<std::string, Window*> WindowManager::_windows;

void WindowManager::init() {
	if (glfwInit() == 0) {
		assert(false && "Failed to initialize GLFW");
	}
	glfwSetErrorCallback([](int, const char* description) {
		utils::Logger::error("GLFW: {}", description);
	});
}

void WindowManager::terminate() {
	for (const auto& [_, window] : _windows) {
		delete window;
	}
	_windows.clear();
	glfwSetErrorCallback(nullptr);
	glfwTerminate();
}

auto WindowManager::create(std::string_view name, std::string_view title, const glm::vec2& size)
	-> Window& {
	assert(_windows.find(std::string(name)) == _windows.end() && "Window already exists");
	auto [it, _] = _windows.emplace(name, new Window(title, size));
	return *it->second;
}

void WindowManager::destroy(std::string_view name) {
	const auto it = _windows.find(std::string(name));
	assert(it != _windows.end() && "Window does not exist");
	delete it->second;
	_windows.erase(it);
}

auto WindowManager::get(std::string_view name) -> Window& {
	auto it = _windows.find(std::string(name));
	assert(it != _windows.end() && "Window does not exist");
	return *it->second;
}

void WindowManager::update() {
	glfwPollEvents();
	for (const auto& [_, window] : _windows) {
		window->update();
	}
}

} // namespace void_engine::window
