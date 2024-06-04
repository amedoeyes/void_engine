#ifndef VOID_ENGINE_WINDOW_WINDOW_HPP
#define VOID_ENGINE_WINDOW_WINDOW_HPP

#include "void_engine/input/input_handler.hpp"

#include <GLFW/glfw3.h>

namespace void_engine::window {

using namespace void_engine::input;

class Window {
public:
	Window(const char* title, int width, int height);
	~Window();

public:
	[[nodiscard]] auto get_window() const -> GLFWwindow*;
	void make_context_current() const;
	void swap_buffers() const;
	[[nodiscard]] auto should_close() const -> bool;
	void close() const;
	[[nodiscard]] auto get_input_handler() const -> InputHandler*;
	[[nodiscard]] auto get_time() const -> float;
	[[nodiscard]] auto get_delta_time() const -> float;

private:
	GLFWwindow* _window;
	InputHandler* _input_handler;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_HPP
