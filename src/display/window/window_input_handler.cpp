module void_engine.display;

import :window.window_event_handler;

namespace void_engine::display::window {

WindowInputHandler::WindowInputHandler(Window& window) :
	_keyboard(input::keyboard::Keyboard(window)),
	_mouse(input::mouse::Mouse(window)) {
}

void WindowInputHandler::update() {
	_keyboard.update();
	_mouse.update();
}

auto WindowInputHandler::get_keyboard() -> input::keyboard::Keyboard& {
	return _keyboard;
}

auto WindowInputHandler::get_mouse() -> input::mouse::Mouse& {
	return _mouse;
}

} // namespace void_engine::display::window
