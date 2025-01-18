module;

#include "void_engine/display/window/hints.hpp"
#include "void_engine/display/window/window.hpp"
#include "void_engine/utility/string_hash.hpp"

#include <GLFW/glfw3.h>

export module window.window_manager;

import std;
import glm;

export namespace void_engine::display::window {

class WindowManager {
public:
	WindowManager(const WindowManager&) = default;
	WindowManager(WindowManager&&) = default;
	auto operator=(const WindowManager&) -> WindowManager& = default;
	auto operator=(WindowManager&&) -> WindowManager& = default;
	WindowManager() = default;
	~WindowManager() {
		for (const auto& [_, window] : _windows) {
			delete window;
		}
	}

	void update() {
		glfwPollEvents();
		for (const auto& [_, window] : _windows) {
			window->update();
		}
	}

	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size,
		const monitor::Monitor& monitor, const Window& share, const Hints& hints = {}
	) -> Window& {
		auto [it, sucess] = _windows.emplace(name, new Window(title, size, monitor, share, hints));
		assert(sucess && "Window already exists");
		return *it->second;
	}

	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size,
		const monitor::Monitor& monitor, const Hints& hints = {}
	) -> Window& {
		auto [it, sucess] = _windows.emplace(name, new Window(title, size, monitor, hints));
		assert(sucess && "Window already exists");
		return *it->second;
	}

	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size, const Window& share,
		const Hints& hints = {}
	) -> Window& {
		auto [it, sucess] = _windows.emplace(name, new Window(title, size, share, hints));
		assert(sucess && "Window already exists");
		return *it->second;
	}

	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size, const Hints& hints = {}
	) -> Window& {
		auto [it, sucess] = _windows.emplace(name, new Window(title, size, hints));
		assert(sucess && "Window already exists");
		return *it->second;
	}

	void destroy(std::string_view name) {
		const auto it = _windows.find(name);
		assert(it != _windows.end() && "Window does not exist");
		delete it->second;
		_windows.erase(it);
	}

	[[nodiscard]] auto get(std::string_view name) -> Window& {
		auto it = _windows.find(name);
		assert(it != _windows.end() && "Window does not exist");
		return *it->second;
	}

	[[nodiscard]] auto get_all() -> std::vector<Window*> {
		return std::ranges::to<std::vector<Window*>>(_windows | std::views::values);
	}

private:
	std::unordered_map<std::string, Window*, utility::string_hash, std::equal_to<>> _windows;
};

} // namespace void_engine::display::window
