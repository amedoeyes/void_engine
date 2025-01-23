export module void_engine.display.window:window_input_handler;

import :window;
import :input.mouse;
import :input.keyboard;

export namespace void_engine::display::window {

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
