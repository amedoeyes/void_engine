#ifndef VOID_ENGINE_INPUT_INPUT_HANDLER_HPP
#define VOID_ENGINE_INPUT_INPUT_HANDLER_HPP

#include <GLFW/glfw3.h>

#include "void_engine/input/keyboard.hpp"
#include "void_engine/input/mouse.hpp"

namespace void_engine::input {

class InputHandler {
	public:
	InputHandler(GLFWwindow* window);
	~InputHandler();

	public:
	void update();

	Keyboard* get_keyboard();
	Mouse* get_mouse();

	private:
	GLFWwindow* _window;
	Keyboard _keyboard;
	Mouse _mouse;
};

}  // namespace void_engine::input

#endif	// !VOID_ENGINE_INPUT_INPUT_HANDLER_HPP
