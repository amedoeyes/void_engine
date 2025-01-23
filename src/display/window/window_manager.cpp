module;

#include "void_engine/utility/string_hash.hpp"

#include <GLFW/glfw3.h>
#include <cassert>

module void_engine.display.window;

import :window_manager;
import :window_hints;

import std;
import glm;
import void_engine.display.monitor;

namespace void_engine::display::window {

WindowManager::~WindowManager() {
	for (const auto& [_, window] : _windows) {
		delete window;
	}
}

void WindowManager::update() {
	glfwPollEvents();
	for (const auto& [_, window] : _windows) {
		window->update();
	}
}

auto WindowManager::create(
	std::string_view name, std::string_view title, const glm::ivec2& size,
	const monitor::Monitor& monitor, const Window& share, const Hints& hints
) -> Window& {
	auto [it, sucess] = _windows.emplace(name, new Window(title, size, monitor, share, hints));
	assert(sucess && "Window already exists");
	return *it->second;
}

auto WindowManager::create(
	std::string_view name, std::string_view title, const glm::ivec2& size,
	const monitor::Monitor& monitor, const Hints& hints
) -> Window& {
	auto [it, sucess] = _windows.emplace(name, new Window(title, size, monitor, hints));
	assert(sucess && "Window already exists");
	return *it->second;
}

auto WindowManager::create(
	std::string_view name, std::string_view title, const glm::ivec2& size, const Window& share,
	const Hints& hints
) -> Window& {
	auto [it, sucess] = _windows.emplace(name, new Window(title, size, share, hints));
	assert(sucess && "Window already exists");
	return *it->second;
}

auto WindowManager::create(
	std::string_view name, std::string_view title, const glm::ivec2& size, const Hints& hints
) -> Window& {
	auto [it, sucess] = _windows.emplace(name, new Window(title, size, hints));
	assert(sucess && "Window already exists");
	return *it->second;
}

void WindowManager::destroy(std::string_view name) {
	const auto it = _windows.find(name);
	assert(it != _windows.end() && "Window does not exist");
	delete it->second;
	_windows.erase(it);
}

auto WindowManager::get(std::string_view name) -> Window& {
	auto it = _windows.find(name);
	assert(it != _windows.end() && "Window does not exist");
	return *it->second;
}

auto WindowManager::get_all() -> std::vector<Window*> {
	return std::ranges::to<std::vector<Window*>>(_windows | std::views::values);
}

} // namespace void_engine::display::window
