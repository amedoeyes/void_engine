module;

#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;
import void_engine.utility.bit_mask;

namespace void_engine::window {

WindowEventHandler::WindowEventHandler(window& window) : _window(&window) {
	glfwSetDropCallback(_window->raw(), [](GLFWwindow* window, int count, const char** paths) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::DropEvent{std::span(paths, count) //
		                         | std::views::transform([](const auto& path) { return std::filesystem::path(path); })
		                         | std::ranges::to<std::vector>()});
	});
	glfwSetFramebufferSizeCallback(_window->raw(), [](GLFWwindow* window, int width, int height) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::FramebufferSizeEvent{glm::vec2(width, height)});
	});
	glfwSetCharCallback(_window->raw(), [](GLFWwindow* window, unsigned int codepoint) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))->events().emit(event::KeyboardCharEvent{codepoint});
	});
	glfwSetCharModsCallback(_window->raw(), [](GLFWwindow* window, unsigned int codepoint, int mods) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::KeyboardCharModsEvent{.codepoint = codepoint, .mods = mods});
	});
	glfwSetKeyCallback(_window->raw(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::KeyboardKeyEvent{
				.key = static_cast<input::keyboard::Key>(key),
				.scancode = scancode,
				.action = static_cast<input::keyboard::KeyAction>(action),
				.mods = utility::BitMask<input::keyboard::KeyMod>(mods),
			});
	});
	glfwSetMouseButtonCallback(_window->raw(), [](GLFWwindow* window, int button, int action, int mods) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::MouseButtonEvent{
				.button = static_cast<input::mouse::Button>(button),
				.action = static_cast<input::mouse::ButtonAction>(action),
				.mods = utility::BitMask<input::keyboard::KeyMod>(mods),
			});
	});
	glfwSetCursorEnterCallback(_window->raw(), [](GLFWwindow* window, int entered) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))->events().emit(event::MouseEnterEvent{entered == 1});
	});
	glfwSetCursorPosCallback(_window->raw(), [](GLFWwindow* window, double xpos, double ypos) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::MousePositionEvent{glm::vec2(xpos, ypos)});
	});
	glfwSetScrollCallback(_window->raw(), [](GLFWwindow* window, double xoffset, double yoffset) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::MouseScrollEvent{glm::vec2(xoffset, yoffset)});
	});
	glfwSetWindowCloseCallback(_window->raw(), [](GLFWwindow* window) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))->events().emit<event::WindowCloseEvent>();
	});
	glfwSetWindowContentScaleCallback(_window->raw(), [](GLFWwindow* window, float xscale, float yscale) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::WindowContentScaleEvent{glm::vec2(xscale, yscale)});
	});
	glfwSetWindowFocusCallback(_window->raw(), [](GLFWwindow* window, int focused) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))->events().emit(event::WindowFocusEvent{focused == 1});
	});
	glfwSetWindowIconifyCallback(_window->raw(), [](GLFWwindow* window, int iconified) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::WindowIconifyEvent{iconified == 1});
	});
	glfwSetWindowMaximizeCallback(_window->raw(), [](GLFWwindow* window, int maximized) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::WindowMaximizeEvent{maximized == 1});
	});
	glfwSetWindowPosCallback(_window->raw(), [](GLFWwindow* window, int xpos, int ypos) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
			.emit(event::WindowPositionEvent{glm::vec2(xpos, ypos)});
	});
	glfwSetWindowRefreshCallback(_window->raw(), [](GLFWwindow* window) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))->events().emit<event::WindowRefreshEvent>();
	});
	glfwSetWindowSizeCallback(_window->raw(), [](GLFWwindow* window, int width, int height) {
		static_cast<class window*>(glfwGetWindowUserPointer(window))
			->events()
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

} // namespace void_engine::window
