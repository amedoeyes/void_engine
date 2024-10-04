#include "void_engine/display/window/input/keyboard/keyboard.hpp"

#include "void_engine/display/window/event/keyboard_key_event.hpp"
#include "void_engine/display/window/input/keyboard/enums.hpp"
#include "void_engine/display/window/window.hpp"
#include "void_engine/display/window/window_event_handler.hpp"
#include <cstddef>

namespace void_engine::display::window::input::keyboard {

Keyboard::Keyboard(Window& window) : _window(&window) {
	_keyboard_key_listener = _window->get_event_handler().add_listener<event::KeyboardKeyEvent>(
		[this](const event::KeyboardKeyEvent& event) {
			set_key(
				event.key,
				event.action == input::keyboard::KeyAction::press ||
					event.action == input::keyboard::KeyAction::repeat
			);
		}
	);
}

Keyboard::~Keyboard() {
	_window->get_event_handler().remove_listener<event::KeyboardKeyEvent>(_keyboard_key_listener);
}

void Keyboard::update() {
	for (auto& key : _keys) {
		key.set_previous(key.get());
	}
}

void Keyboard::set_key(Key key, bool state) {
	_keys[static_cast<size_t>(key)].set_current(state);
}

auto Keyboard::is_down(Key key) const -> bool {
	return _keys[static_cast<size_t>(key)].get();
}

auto Keyboard::is_up(Key key) const -> bool {
	return !_keys[static_cast<size_t>(key)].get();
}

auto Keyboard::is_pressed(Key key) const -> bool {
	return _keys[static_cast<size_t>(key)].entered(true);
}

auto Keyboard::is_released(Key key) const -> bool {
	return _keys[static_cast<size_t>(key)].exited(true);
}

} // namespace void_engine::display::window::input::keyboard
