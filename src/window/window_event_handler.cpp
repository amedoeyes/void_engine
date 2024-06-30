#include "void_engine/window/window_event_handler.hpp"

#include "void_engine/window/window.hpp"

#include <GLFW/glfw3.h>
#include <filesystem>

namespace void_engine::window {

WindowEventHandler::WindowEventHandler(Window* window) : _window(window) {
	GLFWwindow* glfw_window = _window->get_glfw_window();

	glfwSetDropCallback(
		glfw_window,
		[](GLFWwindow* window, int count, const char** paths) {
			std::vector<std::filesystem::path> paths_vector;
			paths_vector.reserve(count);
			for (int i = 0; i < count; ++i) {
				paths_vector.emplace_back(paths[i]);
			}
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::DropEvent>(paths_vector);
		}
	);

	glfwSetFramebufferSizeCallback(
		glfw_window,
		[](GLFWwindow* window, int width, int height) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::FramebufferSizeEvent>(glm::vec2(width, height));
		}
	);

	glfwSetCharCallback(
		glfw_window,
		[](GLFWwindow* window, unsigned int codepoint) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::KeyboardCharEvent>(codepoint);
		}
	);

	glfwSetCharModsCallback(
		glfw_window,
		[](GLFWwindow* window, unsigned int codepoint, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::KeyboardCharModsEvent>(codepoint, mods);
		}
	);

	glfwSetKeyCallback(
		glfw_window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::KeyboardKeyEvent>(key, scancode, action, mods);
		}
	);

	glfwSetMouseButtonCallback(
		glfw_window,
		[](GLFWwindow* window, int button, int action, int mods) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::MouseButtonEvent>(button, action, mods);
		}
	);

	glfwSetCursorEnterCallback(
		glfw_window,
		[](GLFWwindow* window, int entered) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::MouseEnterEvent>(entered == 1);
		}
	);

	glfwSetCursorPosCallback(
		glfw_window,
		[](GLFWwindow* window, double xpos, double ypos) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::MousePositionEvent>(glm::vec2(xpos, ypos));
		}
	);

	glfwSetScrollCallback(
		glfw_window,
		[](GLFWwindow* window, double xoffset, double yoffset) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::MouseScrollEvent>(glm::vec2(xoffset, yoffset));
		}
	);

	glfwSetWindowCloseCallback(glfw_window, [](GLFWwindow* window) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->event_handler()
			->emit<events::WindowCloseEvent>();
	});

	glfwSetWindowContentScaleCallback(
		glfw_window,
		[](GLFWwindow* window, float xscale, float yscale) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::WindowContentScaleEvent>(
					glm::vec2(xscale, yscale)
				);
		}
	);

	glfwSetWindowFocusCallback(
		glfw_window,
		[](GLFWwindow* window, int focused) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::WindowFocusEvent>(focused == 1);
		}
	);

	glfwSetWindowIconifyCallback(
		glfw_window,
		[](GLFWwindow* window, int iconified) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::WindowIconifyEvent>(iconified == 1);
		}
	);

	glfwSetWindowMaximizeCallback(
		glfw_window,
		[](GLFWwindow* window, int maximized) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::WindowMaximizeEvent>(maximized == 1);
		}
	);

	glfwSetWindowPosCallback(
		glfw_window,
		[](GLFWwindow* window, int xpos, int ypos) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::WindowPositionEvent>(glm::vec2(xpos, ypos));
		}
	);

	glfwSetWindowRefreshCallback(glfw_window, [](GLFWwindow* window) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))
			->event_handler()
			->emit<events::WindowRefreshEvent>();
	});

	glfwSetWindowSizeCallback(
		glfw_window,
		[](GLFWwindow* window, int width, int height) {
			static_cast<Window*>(glfwGetWindowUserPointer(window))
				->event_handler()
				->emit<events::WindowSizeEvent>(glm::vec2(width, height));
		}
	);
}

WindowEventHandler::~WindowEventHandler() {
	GLFWwindow* glfw_window = _window->get_glfw_window();
	glfwSetCharCallback(glfw_window, nullptr);
	glfwSetCharModsCallback(glfw_window, nullptr);
	glfwSetCursorEnterCallback(glfw_window, nullptr);
	glfwSetCursorPosCallback(glfw_window, nullptr);
	glfwSetDropCallback(glfw_window, nullptr);
	glfwSetFramebufferSizeCallback(glfw_window, nullptr);
	glfwSetKeyCallback(glfw_window, nullptr);
	glfwSetMouseButtonCallback(glfw_window, nullptr);
	glfwSetScrollCallback(glfw_window, nullptr);
	glfwSetWindowCloseCallback(glfw_window, nullptr);
	glfwSetWindowContentScaleCallback(glfw_window, nullptr);
	glfwSetWindowFocusCallback(glfw_window, nullptr);
	glfwSetWindowIconifyCallback(glfw_window, nullptr);
	glfwSetWindowMaximizeCallback(glfw_window, nullptr);
	glfwSetWindowPosCallback(glfw_window, nullptr);
	glfwSetWindowRefreshCallback(glfw_window, nullptr);
	glfwSetWindowSizeCallback(glfw_window, nullptr);
}

void WindowEventHandler::poll() {
	_event_manager.poll();
}

} // namespace void_engine::window
