#include "void_engine/display/window/window_event_handler.hpp"

#include "void_engine/display/window/event/drop_event.hpp"
#include "void_engine/display/window/event/framebuffer_size_event.hpp"
#include "void_engine/display/window/event/keyboard_char_event.hpp"
#include "void_engine/display/window/event/keyboard_char_mods_event.hpp"
#include "void_engine/display/window/event/keyboard_key_event.hpp"
#include "void_engine/display/window/event/mouse_button_event.hpp"
#include "void_engine/display/window/event/mouse_enter_event.hpp"
#include "void_engine/display/window/event/mouse_position_event.hpp"
#include "void_engine/display/window/event/mouse_scroll_event.hpp"
#include "void_engine/display/window/event/window_close_event.hpp"
#include "void_engine/display/window/event/window_content_scale_event.hpp"
#include "void_engine/display/window/event/window_focus_event.hpp"
#include "void_engine/display/window/event/window_iconify_event.hpp"
#include "void_engine/display/window/event/window_maximize_event.hpp"
#include "void_engine/display/window/event/window_position_event.hpp"
#include "void_engine/display/window/event/window_refresh_event.hpp"
#include "void_engine/display/window/event/window_size_event.hpp"
#include "void_engine/display/window/window.hpp"

#include <GLFW/glfw3.h>
#include <filesystem>
#include <vector>

namespace void_engine::display::window {

WindowEventHandler::WindowEventHandler(Window& window) : _window(&window) {
	glfwSetDropCallback(_window->_window, [](GLFWwindow* window, int count, const char** paths) {
		std::vector<std::filesystem::path> paths_vector;
		paths_vector.reserve(count);
		for (int i = 0; i < count; ++i) {
			paths_vector.emplace_back(paths[i]);
		}
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::DropEvent{paths_vector});
	});
	glfwSetFramebufferSizeCallback(_window->_window, [](GLFWwindow* window, int width, int height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::FramebufferSizeEvent{glm::vec2(width, height)});
	});
	glfwSetCharCallback(_window->_window, [](GLFWwindow* window, unsigned int codepoint) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::KeyboardCharEvent{codepoint});
	});
	glfwSetCharModsCallback(
		_window->_window,
		[](GLFWwindow* window, unsigned int codepoint, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(event::KeyboardCharModsEvent{.codepoint = codepoint, .mods = mods});
		}
	);
	glfwSetKeyCallback(
		_window->_window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(
					event::KeyboardKeyEvent{.key = key, .scancode = scancode, .action = action, .mods = mods}
				);
		}
	);
	glfwSetMouseButtonCallback(
		_window->_window,
		[](GLFWwindow* window, int button, int action, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(event::MouseButtonEvent{.button = button, .action = action, .mods = mods});
		}
	);
	glfwSetCursorEnterCallback(_window->_window, [](GLFWwindow* window, int entered) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::MouseEnterEvent{entered == 1});
	});
	glfwSetCursorPosCallback(_window->_window, [](GLFWwindow* window, double xpos, double ypos) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::MousePositionEvent{glm::vec2(xpos, ypos)});
	});
	glfwSetScrollCallback(_window->_window, [](GLFWwindow* window, double xoffset, double yoffset) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::MouseScrollEvent{glm::vec2(xoffset, yoffset)});
	});
	glfwSetWindowCloseCallback(_window->_window, [](GLFWwindow* window) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit<event::WindowCloseEvent>();
	});
	glfwSetWindowContentScaleCallback(
		_window->_window,
		[](GLFWwindow* window, float xscale, float yscale) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->get_event_handler()
				.emit(event::WindowContentScaleEvent{glm::vec2(xscale, yscale)});
		}
	);
	glfwSetWindowFocusCallback(_window->_window, [](GLFWwindow* window, int focused) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowFocusEvent{focused == 1});
	});
	glfwSetWindowIconifyCallback(_window->_window, [](GLFWwindow* window, int iconified) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowIconifyEvent{iconified == 1});
	});
	glfwSetWindowMaximizeCallback(_window->_window, [](GLFWwindow* window, int maximized) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowMaximizeEvent{maximized == 1});
	});
	glfwSetWindowPosCallback(_window->_window, [](GLFWwindow* window, int xpos, int ypos) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowPositionEvent{glm::vec2(xpos, ypos)});
	});
	glfwSetWindowRefreshCallback(_window->_window, [](GLFWwindow* window) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit<event::WindowRefreshEvent>();
	});
	glfwSetWindowSizeCallback(_window->_window, [](GLFWwindow* window, int width, int height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->get_event_handler()
			.emit(event::WindowSizeEvent{glm::vec2(width, height)});
	});
}

WindowEventHandler::~WindowEventHandler() {
	glfwSetCharCallback(_window->_window, nullptr);
	glfwSetCharModsCallback(_window->_window, nullptr);
	glfwSetCursorEnterCallback(_window->_window, nullptr);
	glfwSetCursorPosCallback(_window->_window, nullptr);
	glfwSetDropCallback(_window->_window, nullptr);
	glfwSetFramebufferSizeCallback(_window->_window, nullptr);
	glfwSetKeyCallback(_window->_window, nullptr);
	glfwSetMouseButtonCallback(_window->_window, nullptr);
	glfwSetScrollCallback(_window->_window, nullptr);
	glfwSetWindowCloseCallback(_window->_window, nullptr);
	glfwSetWindowContentScaleCallback(_window->_window, nullptr);
	glfwSetWindowFocusCallback(_window->_window, nullptr);
	glfwSetWindowIconifyCallback(_window->_window, nullptr);
	glfwSetWindowMaximizeCallback(_window->_window, nullptr);
	glfwSetWindowPosCallback(_window->_window, nullptr);
	glfwSetWindowRefreshCallback(_window->_window, nullptr);
	glfwSetWindowSizeCallback(_window->_window, nullptr);
}

} // namespace void_engine::display::window
