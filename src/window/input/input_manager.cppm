export module void_engine.window:input.input_manager;

import :input.keyboard;
import :input.mouse;

export namespace void_engine::window {
class window;
}  // namespace void_engine::window

export namespace void_engine::window::input {

class InputManager {
public:
	InputManager(const InputManager&) = default;
	InputManager(InputManager&&) = default;
	auto operator=(const InputManager&) -> InputManager& = default;
	auto operator=(InputManager&&) -> InputManager& = default;
	InputManager() = delete;
	explicit InputManager(window& window);
	~InputManager() = default;

	void update();

	[[nodiscard]]
	auto get_keyboard() -> keyboard::Keyboard&;
	[[nodiscard]]
	auto get_mouse() -> mouse::Mouse&;

private:
	keyboard::Keyboard _keyboard;
	mouse::Mouse _mouse;
};

} // namespace void_engine::window::input
