#ifndef VOID_ENGINE_WINDOW_WINDOW_HPP
#define VOID_ENGINE_WINDOW_WINDOW_HPP

#include "void_engine/window/window_event_handler.hpp"
#include "void_engine/window/window_input_handler.hpp"

#include <glm/ext/vector_float2.hpp>
#include <string_view>

struct GLFWwindow;

namespace void_engine::window {

class Window {
	friend class WindowEventHandler;
	friend class WindowInputHandler;

public:
	Window(const std::string_view title, const glm::vec2& size);
	~Window();

	void make_context_current() const;
	void swap_buffers() const;
	void close() const;

	[[nodiscard]] auto event_handler() -> WindowEventHandler*;
	[[nodiscard]] auto input_handler() -> WindowInputHandler*;

	[[nodiscard]] auto should_close() const -> bool;
	[[nodiscard]] auto get_size() const -> glm::vec2;
	[[nodiscard]] auto get_time() const -> float;
	[[nodiscard]] auto get_delta_time() const -> float;

private:
	GLFWwindow* _window;
	WindowEventHandler* _event_handler;
	WindowInputHandler* _input_handler;

	[[nodiscard]] auto get_glfw_window() -> GLFWwindow*;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_HPP
