#include "void_engine/input/input_handler.hpp"

#include "void_engine/input/keyboard.hpp"
#include "void_engine/input/mouse.hpp"

#include <GLFW/glfw3.h>

namespace void_engine::input {

InputHandler::InputHandler(GLFWwindow* window) : _window(window) {
	glfwSetKeyCallback(_window, _keyboard.callback);
	glfwSetMouseButtonCallback(_window, _mouse.button_callback);
	glfwSetCursorPosCallback(_window, _mouse.position_callback);
	glfwSetScrollCallback(_window, _mouse.scroll_callback);
}

InputHandler::~InputHandler() {
	glfwSetKeyCallback(_window, nullptr);
	glfwSetMouseButtonCallback(_window, nullptr);
	glfwSetCursorPosCallback(_window, nullptr);
	glfwSetScrollCallback(_window, nullptr);
}

void InputHandler::update() {
	_keyboard.update();
	_mouse.update();
}

auto InputHandler::get_keyboard() -> Keyboard* {
	return &_keyboard;
}

auto InputHandler::get_mouse() -> Mouse* {
	return &_mouse;
}

} // namespace void_engine::input
