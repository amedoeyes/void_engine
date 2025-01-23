module;

#include "void_engine/utility/bit_mask.hpp"

#include <GLFW/glfw3.h>

module void_engine.display;

import :input.keyboard.enums;
import :input.mouse.enums;
import :window.window_event_handler;
import :window.window_events;

import std;
import glm;

namespace void_engine::display::window {

WindowEventHandler::WindowEventHandler(Window& window) : _window(&window) {
	glfwSetDropCallback(_window->raw(), [](GLFWwindow* window, int count, const char** paths) {
		std::vector<std::filesystem::path> paths_vector;
		paths_vector.reserve(count);
		for (int i = 0; i < count; ++i) {
			paths_vector.emplace_back(paths[i]);
		}
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::DropEvent{paths_vector});
	});
	glfwSetFramebufferSizeCallback(_window->raw(), [](GLFWwindow* window, int width, int height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::FramebufferSizeEvent{glm::vec2(width, height)});
	});
	glfwSetCharCallback(_window->raw(), [](GLFWwindow* window, unsigned int codepoint) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::KeyboardCharEvent{codepoint});
	});
	glfwSetCharModsCallback(_window->raw(), [](GLFWwindow* window, unsigned int codepoint, int mods) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::KeyboardCharModsEvent{.codepoint = codepoint, .mods = mods});
	});
	glfwSetKeyCallback(
		_window->raw(),
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(event::KeyboardKeyEvent{
					.key = static_cast<input::keyboard::Key>(key),
					.scancode = scancode,
					.action = static_cast<input::keyboard::KeyAction>(action),
					.mods = utility::BitMask<input::keyboard::KeyMod>(mods),
				});
		}
	);
	glfwSetMouseButtonCallback(
		_window->raw(),
		[](GLFWwindow* window, int button, int action, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(event::MouseButtonEvent{
					.button = static_cast<input::mouse::Button>(button),
					.action = static_cast<input::mouse::ButtonAction>(action),
					.mods = utility::BitMask<input::keyboard::KeyMod>(mods),
				});
		}
	);
	glfwSetCursorEnterCallback(_window->raw(), [](GLFWwindow* window, int entered) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::MouseEnterEvent{entered == 1});
	});
	glfwSetCursorPosCallback(_window->raw(), [](GLFWwindow* window, double xpos, double ypos) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::MousePositionEvent{glm::vec2(xpos, ypos)});
	});
	glfwSetScrollCallback(_window->raw(), [](GLFWwindow* window, double xoffset, double yoffset) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::MouseScrollEvent{glm::vec2(xoffset, yoffset)});
	});
	glfwSetWindowCloseCallback(_window->raw(), [](GLFWwindow* window) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit<event::WindowCloseEvent>();
	});
	glfwSetWindowContentScaleCallback(
		_window->raw(),
		[](GLFWwindow* window, float xscale, float yscale) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(event::WindowContentScaleEvent{glm::vec2(xscale, yscale)});
		}
	);
	glfwSetWindowFocusCallback(_window->raw(), [](GLFWwindow* window, int focused) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowFocusEvent{focused == 1});
	});
	glfwSetWindowIconifyCallback(_window->raw(), [](GLFWwindow* window, int iconified) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowIconifyEvent{iconified == 1});
	});
	glfwSetWindowMaximizeCallback(_window->raw(), [](GLFWwindow* window, int maximized) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowMaximizeEvent{maximized == 1});
	});
	glfwSetWindowPosCallback(_window->raw(), [](GLFWwindow* window, int xpos, int ypos) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowPositionEvent{glm::vec2(xpos, ypos)});
	});
	glfwSetWindowRefreshCallback(_window->raw(), [](GLFWwindow* window) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit<event::WindowRefreshEvent>();
	});
	glfwSetWindowSizeCallback(_window->raw(), [](GLFWwindow* window, int width, int height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowSizeEvent{glm::vec2(width, height)});
	});
}

WindowEventHandler::~WindowEventHandler() {
	glfwSetCharCallback(_window->raw(), nullptr);
	glfwSetCharModsCallback(_window->raw(), nullptr);
	glfwSetCursorEnterCallback(_window->raw(), nullptr);
	glfwSetCursorPosCallback(_window->raw(), nullptr);
	glfwSetDropCallback(_window->raw(), nullptr);
	glfwSetFramebufferSizeCallback(_window->raw(), nullptr);
	glfwSetKeyCallback(_window->raw(), nullptr);
	glfwSetMouseButtonCallback(_window->raw(), nullptr);
	glfwSetScrollCallback(_window->raw(), nullptr);
	glfwSetWindowCloseCallback(_window->raw(), nullptr);
	glfwSetWindowContentScaleCallback(_window->raw(), nullptr);
	glfwSetWindowFocusCallback(_window->raw(), nullptr);
	glfwSetWindowIconifyCallback(_window->raw(), nullptr);
	glfwSetWindowMaximizeCallback(_window->raw(), nullptr);
	glfwSetWindowPosCallback(_window->raw(), nullptr);
	glfwSetWindowRefreshCallback(_window->raw(), nullptr);
	glfwSetWindowSizeCallback(_window->raw(), nullptr);
}

} // namespace void_engine::display::window
