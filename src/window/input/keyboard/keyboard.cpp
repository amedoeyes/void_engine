module void_engine.window;

import std;

namespace void_engine::window::input::keyboard {

Keyboard::Keyboard(window::Window& window) : _window(&window) {
	_keyboard_key_listener = _window->get_events().add_listener<window::event::KeyboardKeyEvent>(
		[this](const window::event::KeyboardKeyEvent& event) {
			set_key(event.key, event.action == KeyAction::press || event.action == KeyAction::repeat);
		}
	);
}

Keyboard::~Keyboard() {
	_window->get_events().remove_listener<window::event::KeyboardKeyEvent>(_keyboard_key_listener);
}

void Keyboard::update() {
	for (auto& key : _keys) {
		key.set_previous(key.get());
	}
}

void Keyboard::set_key(Key key, bool state) {
	_keys[static_cast<std::size_t>(key)].set_current(state);
}

auto Keyboard::is_down(Key key) const -> bool {
	return _keys[static_cast<std::size_t>(key)].get();
}

auto Keyboard::is_up(Key key) const -> bool {
	return !_keys[static_cast<std::size_t>(key)].get();
}

auto Keyboard::is_pressed(Key key) const -> bool {
	return _keys[static_cast<std::size_t>(key)].entered(true);
}

auto Keyboard::is_released(Key key) const -> bool {
	return _keys[static_cast<std::size_t>(key)].exited(true);
}

} // namespace void_engine::window::input::keyboard
