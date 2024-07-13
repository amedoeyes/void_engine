#include "void_engine/window/window_input_handler.hpp"

#include "void_engine/window/events/keyboard_key_event.hpp"
#include "void_engine/window/events/mouse_button_event.hpp"
#include "void_engine/window/events/mouse_position_event.hpp"
#include "void_engine/window/events/mouse_scroll_event.hpp"
#include "void_engine/window/inputs/keyboard.hpp"
#include "void_engine/window/inputs/mouse.hpp"
#include "void_engine/window/window.hpp"
#include "void_engine/window/window_event_handler.hpp"

namespace void_engine::window {

WindowInputHandler::WindowInputHandler(Window& window) : _window(&window) {
	using namespace events;
	using namespace inputs;
	WindowEventHandler& events = _window->event_handler();
	_keyboard_key_listener =
		events.add_listener<KeyboardKeyEvent>([this](const KeyboardKeyEvent& event) {
			_keyboard.set_key(static_cast<KeyboardKey>(event.key), event.action > 0);
		});
	_mouse_button_listener =
		events.add_listener<MouseButtonEvent>([this](const MouseButtonEvent& event) {
			_mouse.set_button(static_cast<MouseButton>(event.button), event.action == 1);
		});
	_mouse_position_listener =
		events.add_listener<MousePositionEvent>([this](const MousePositionEvent& event) {
			_mouse.set_position(event.position);
		});
	_mouse_scroll_listener =
		events.add_listener<MouseScrollEvent>([this](const MouseScrollEvent& event) {
			_mouse.set_scroll(event.offset);
		});
}

WindowInputHandler::~WindowInputHandler() {
	WindowEventHandler& events = _window->event_handler();
	events.remove_listener(_keyboard_key_listener);
	events.remove_listener(_mouse_button_listener);
	events.remove_listener(_mouse_position_listener);
	events.remove_listener(_mouse_scroll_listener);
}

void WindowInputHandler::update() {
	_keyboard.update();
	_mouse.update();
}

auto WindowInputHandler::get_keyboard() const -> const inputs::Keyboard& {
	return _keyboard;
}

auto WindowInputHandler::get_mouse() const -> const inputs::Mouse& {
	return _mouse;
}

} // namespace void_engine::window
