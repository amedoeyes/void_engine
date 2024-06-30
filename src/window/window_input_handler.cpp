#include "void_engine/window/window_input_handler.hpp"

#include "void_engine/window/events/keyboard_key_event.hpp"
#include "void_engine/window/events/mouse_button_event.hpp"
#include "void_engine/window/events/mouse_position_event.hpp"
#include "void_engine/window/events/mouse_scroll_event.hpp"
#include "void_engine/window/inputs/keyboard.hpp"
#include "void_engine/window/inputs/mouse.hpp"
#include "void_engine/window/window.hpp"
#include "void_engine/window/window_event_handler.hpp"

#include <GLFW/glfw3.h>

namespace void_engine::window {

WindowInputHandler::WindowInputHandler(Window* window) :
	_window(window), _keyboard(new inputs::Keyboard()),
	_mouse(new inputs::Mouse()) {
	WindowEventHandler* event_handler = window->event_handler();

	_keyboard_key_listener =
		event_handler->add_listener<events::KeyboardKeyEvent>(
			[this](const events::KeyboardKeyEvent& event) {
				_keyboard->set_key(
					static_cast<inputs::KeyboardKey>(event.key),
					event.action > 0
				);
			}
		);

	_mouse_button_listener =
		event_handler->add_listener<events::MouseButtonEvent>(
			[this](const events::MouseButtonEvent& event) {
				_mouse->set_button(
					static_cast<inputs::MouseButton>(event.button),
					event.action == 1
				);
			}
		);

	_mouse_position_listener =
		event_handler->add_listener<events::MousePositionEvent>(
			[this](const events::MousePositionEvent& event) {
				_mouse->set_position(event.position);
			}
		);

	_mouse_scroll_listener =
		event_handler->add_listener<events::MouseScrollEvent>(
			[this](const events::MouseScrollEvent& event) {
				_mouse->set_scroll(event.offset);
			}
		);
}

WindowInputHandler::~WindowInputHandler() {
	WindowEventHandler* event_handler = _window->event_handler();
	event_handler->remove_listener<events::KeyboardKeyEvent>(
		_keyboard_key_listener
	);
	event_handler->remove_listener<events::MouseButtonEvent>(
		_mouse_button_listener
	);
	event_handler->remove_listener<events::MousePositionEvent>(
		_mouse_position_listener
	);
	event_handler->remove_listener<events::MouseScrollEvent>(
		_mouse_scroll_listener
	);
}

void WindowInputHandler::update() {
	_keyboard->update();
	_mouse->update();
}

auto WindowInputHandler::get_keyboard() const -> const inputs::Keyboard* {
	return _keyboard;
}

auto WindowInputHandler::get_mouse() const -> const inputs::Mouse* {
	return _mouse;
}

} // namespace void_engine::window
