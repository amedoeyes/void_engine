#include "void_engine/display/window/window_input_handler.hpp"

#include "void_engine/display/window/event/keyboard_key_event.hpp"
#include "void_engine/display/window/event/mouse_button_event.hpp"
#include "void_engine/display/window/event/mouse_position_event.hpp"
#include "void_engine/display/window/event/mouse_scroll_event.hpp"
#include "void_engine/display/window/input/keyboard.hpp"
#include "void_engine/display/window/input/mouse.hpp"
#include "void_engine/display/window/window.hpp"
#include "void_engine/display/window/window_event_handler.hpp"
#include "void_engine/utility/event.hpp"

namespace void_engine::display::window {

WindowInputHandler::WindowInputHandler(Window& window) :
	_window(&window),
	_keyboard(new input::Keyboard),
	_mouse(new input::Mouse(*window._window)) {
	WindowEventHandler& events = _window->get_event_handler();
	_keyboard_key_listener =
		events.add_listener<event::KeyboardKeyEvent>([this](const event::KeyboardKeyEvent& event) {
			_keyboard->set_key(static_cast<input::KeyboardKey>(event.key), event.action > 0);
		});
	_mouse_button_listener =
		events.add_listener<event::MouseButtonEvent>([this](const event::MouseButtonEvent& event) {
			_mouse->set_button(static_cast<input::MouseButton>(event.button), event.action == 1);
		});
	_mouse_position_listener =
		events.add_listener<event::MousePositionEvent>([this](const event::MousePositionEvent& event) {
			_mouse->set_position(event.position);
		});
	_mouse_scroll_listener =
		events.add_listener<event::MouseScrollEvent>([this](const event::MouseScrollEvent& event) {
			_mouse->set_scroll(event.offset);
		});
}

WindowInputHandler::~WindowInputHandler() {
	delete _keyboard;
	delete _mouse;
	WindowEventHandler& events = _window->get_event_handler();
	events.remove_listener<event::KeyboardKeyEvent>(_keyboard_key_listener);
	events.remove_listener<event::MouseButtonEvent>(_mouse_button_listener);
	events.remove_listener<event::MousePositionEvent>(_mouse_position_listener);
	events.remove_listener<event::MouseScrollEvent>(_mouse_scroll_listener);
}

void WindowInputHandler::update() {
	_keyboard->update();
	_mouse->update();
}

auto WindowInputHandler::get_keyboard() -> input::Keyboard& {
	return *_keyboard;
}

auto WindowInputHandler::get_mouse() -> input::Mouse& {
	return *_mouse;
}

} // namespace void_engine::display::window
