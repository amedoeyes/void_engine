#ifndef VOID_WINDOW_HPP
#define VOID_WINDOW_HPP

#include <GLFW/glfw3.h>

namespace void_engine::window {

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

	private:
	GLFWwindow* _window;
};

}  // namespace void_engine::window

#endif	// !VOID_WINDOW_HPP
