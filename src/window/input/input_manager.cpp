module void_engine.window;

namespace void_engine::window::input {

InputManager::InputManager(Window& window) : _keyboard(window), _mouse(window) {
}

void InputManager::update() {
	_keyboard.update();
	_mouse.update();
}

auto InputManager::get_keyboard() -> input::keyboard::Keyboard& {
	return _keyboard;
}

auto InputManager::get_mouse() -> input::mouse::Mouse& {
	return _mouse;
}

} // namespace void_engine::window::input
