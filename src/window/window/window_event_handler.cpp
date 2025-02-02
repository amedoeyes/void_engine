module;

#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;
import void_engine.utility.bit_mask;

namespace void_engine::window {

window_event_bus::window_event_bus(const window& window) : window_{window.raw()} {
	static constexpr auto emit = [](GLFWwindow* w, auto&& data) {
		return static_cast<class window*>(glfwGetWindowUserPointer(w))->events().emit(std::forward<decltype(data)>(data));
	};
	glfwSetDropCallback(window_, [](GLFWwindow* w, int count, const char** paths) {
		emit(w, event::drop{std::span(paths, count) | std::views::transform([](const auto& path) {
			return std::filesystem::path(path);
		}) | std::ranges::to<std::vector>()});
	});
	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* w, int width, int height) {
		emit(w, event::framebuffer_size{glm::vec2(width, height)});
	});
	glfwSetCharCallback(window_, [](GLFWwindow* w, unsigned int codepoint) { emit(w, event::keyboard_char{codepoint}); });
	glfwSetCharModsCallback(window_, [](GLFWwindow* w, unsigned int codepoint, int mods) {
		emit(w, event::keyboard_char_mods{.codepoint = codepoint, .mods = mods});
	});
	glfwSetKeyCallback(window_, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
		emit(w,
		     event::keyboard_key{
					 .key = static_cast<input::keyboard_key>(key),
					 .scancode = scancode,
					 .action = static_cast<input::keyboard_action>(action),
					 .mods = utility::BitMask<input::keyboard_mod>(mods),
				 });
	});
	glfwSetMouseButtonCallback(window_, [](GLFWwindow* w, int button, int action, int mods) {
		emit(w,
		     event::mouse_button{
					 .button = static_cast<input::mouse_button>(button),
					 .action = static_cast<input::mouse_action>(action),
					 .mods = utility::BitMask<input::keyboard_mod>(mods),
				 });
	});
	glfwSetCursorEnterCallback(window_, [](GLFWwindow* w, int entered) { emit(w, event::mouse_enter{entered == 1}); });
	glfwSetCursorPosCallback(window_, [](GLFWwindow* w, double xpos, double ypos) {
		emit(w, event::mouse_position{glm::vec2(xpos, ypos)});
	});
	glfwSetScrollCallback(window_, [](GLFWwindow* w, double xoffset, double yoffset) {
		emit(w, event::mouse_scroll{glm::vec2(xoffset, yoffset)});
	});
	glfwSetWindowCloseCallback(window_, [](GLFWwindow* w) { emit(w, event::window_close{}); });
	glfwSetWindowContentScaleCallback(window_, [](GLFWwindow* w, float xscale, float yscale) {
		emit(w, event::window_content_scale{glm::vec2(xscale, yscale)});
	});
	glfwSetWindowFocusCallback(window_, [](GLFWwindow* w, int focused) { emit(w, event::window_focus{focused == 1}); });
	glfwSetWindowIconifyCallback(window_,
	                             [](GLFWwindow* w, int iconified) { emit(w, event::window_iconify{iconified == 1}); });
	glfwSetWindowMaximizeCallback(window_,
	                              [](GLFWwindow* w, int maximized) { emit(w, event::window_maximize{maximized == 1}); });
	glfwSetWindowPosCallback(window_, [](GLFWwindow* w, int xpos, int ypos) {
		emit(w, event::window_position{glm::vec2(xpos, ypos)});
	});
	glfwSetWindowRefreshCallback(window_, [](GLFWwindow* w) { emit(w, event::window_refresh{}); });
	glfwSetWindowSizeCallback(window_, [](GLFWwindow* w, int width, int height) {
		emit(w, event::window_size{glm::vec2(width, height)});
	});
}

window_event_bus::~window_event_bus() {
	glfwSetCharCallback(window_, nullptr);
	glfwSetCharModsCallback(window_, nullptr);
	glfwSetCursorEnterCallback(window_, nullptr);
	glfwSetCursorPosCallback(window_, nullptr);
	glfwSetDropCallback(window_, nullptr);
	glfwSetFramebufferSizeCallback(window_, nullptr);
	glfwSetKeyCallback(window_, nullptr);
	glfwSetMouseButtonCallback(window_, nullptr);
	glfwSetScrollCallback(window_, nullptr);
	glfwSetWindowCloseCallback(window_, nullptr);
	glfwSetWindowContentScaleCallback(window_, nullptr);
	glfwSetWindowFocusCallback(window_, nullptr);
	glfwSetWindowIconifyCallback(window_, nullptr);
	glfwSetWindowMaximizeCallback(window_, nullptr);
	glfwSetWindowPosCallback(window_, nullptr);
	glfwSetWindowRefreshCallback(window_, nullptr);
	glfwSetWindowSizeCallback(window_, nullptr);
}

} // namespace void_engine::window
