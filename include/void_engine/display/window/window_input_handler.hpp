#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP

#include "void_engine/display/window/input/keyboard/keyboard.hpp"
#include "void_engine/display/window/input/mouse/mouse.hpp"

namespace void_engine::display::window {

class Window;

class WindowInputHandler {
public:
	WindowInputHandler(const WindowInputHandler&) = default;
	WindowInputHandler(WindowInputHandler&&) = delete;
	auto operator=(const WindowInputHandler&) -> WindowInputHandler& = default;
	auto operator=(WindowInputHandler&&) -> WindowInputHandler& = delete;
	WindowInputHandler() = delete;
	explicit WindowInputHandler(Window& window);
	~WindowInputHandler() = default;

	void update();

	[[nodiscard]] auto get_keyboard() -> input::keyboard::Keyboard&;
	[[nodiscard]] auto get_mouse() -> input::mouse::Mouse&;

private:
	input::keyboard::Keyboard _keyboard;
	input::mouse::Mouse _mouse;
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP
