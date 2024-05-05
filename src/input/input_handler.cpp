#include "void_engine/input/input_handler.hpp"

#include <GLFW/glfw3.h>

#include "void_engine/input/keyboard.hpp"

namespace void_engine::input {

InputHandler::InputHandler(GLFWwindow* window) : _window(window) {
	glfwSetWindowUserPointer(_window, static_cast<void*>(this));
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

Keyboard* InputHandler::get_keyboard() {
	return &_keyboard;
}

Mouse* InputHandler::get_mouse() {
	return &_mouse;
}

}  // namespace void_engine::input
