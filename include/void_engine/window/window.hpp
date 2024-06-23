#ifndef VOID_ENGINE_WINDOW_WINDOW_HPP
#define VOID_ENGINE_WINDOW_WINDOW_HPP

#include "void_engine/input/input_handler.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <string_view>

namespace void_engine::window {

class Window {
public:
	Window(const std::string_view title, int width, int height);
	~Window();

public:
	[[nodiscard]] auto get_window() const -> GLFWwindow*;
	void make_context_current() const;
	void swap_buffers() const;
	[[nodiscard]] auto should_close() const -> bool;
	void close() const;
	[[nodiscard]] auto get_input_handler() const
		-> void_engine::input::InputHandler*;
	[[nodiscard]] auto get_time() const -> float;
	[[nodiscard]] auto get_delta_time() const -> float;
	[[nodiscard]] auto get_size() const -> glm::vec2;

private:
	GLFWwindow* _window;
	void_engine::input::InputHandler* _input_handler;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_HPP
