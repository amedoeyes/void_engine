module void_engine.window;

import std;

namespace void_engine::window::input::keyboard {

Keyboard::Keyboard(window& window) : _window(&window) {
	_keyboard_key_listener = _window->events().add_listener<event::keyboard_key>([this](const auto& event) {
		set_key(event.key, event.action == KeyAction::press || event.action == KeyAction::repeat);
	});
}

Keyboard::~Keyboard() { _window->events().remove_listener<event::keyboard_key>(_keyboard_key_listener); }

void Keyboard::update() {
	for (auto& key : _keys) key.set_previous(key.get());
}

void Keyboard::set_key(Key key, bool state) { _keys.at(std::to_underlying(key)).set_current(state); }

auto Keyboard::is_down(Key key) const -> bool { return _keys.at(std::to_underlying(key)).get(); }

auto Keyboard::is_up(Key key) const -> bool { return !_keys.at(std::to_underlying(key)).get(); }

auto Keyboard::is_pressed(Key key) const -> bool { return _keys.at(std::to_underlying(key)).entered(true); }

auto Keyboard::is_released(Key key) const -> bool { return _keys.at(std::to_underlying(key)).exited(true); }

} // namespace void_engine::window::input::keyboard
