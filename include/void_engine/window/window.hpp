#ifndef VOID_ENGINE_WINDOW_HPP
#define VOID_ENGINE_WINDOW_HPP

#include <GLFW/glfw3.h>

#include "void_engine/input/input_handler.hpp"

namespace void_engine::window {

using namespace void_engine::input;

class Window {
	public:
	Window(const char* title, const int& width, const int& height);
	~Window();

	public:
	GLFWwindow* get_window() const;
	void make_context_current() const;
	void swap_buffers() const;
	bool should_close() const;
	void close() const;
	InputHandler* get_input_handler() const;
	float get_time() const;

	private:
	GLFWwindow* _window;
	InputHandler* _input_handler;
};

}  // namespace void_engine::window

#endif	// !VOID_ENGINE_WINDOW_HPP
