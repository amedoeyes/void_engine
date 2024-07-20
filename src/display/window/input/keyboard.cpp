#include "void_engine/display/window/input/keyboard.hpp"

namespace void_engine::display::window::input {

auto Keyboard::is_down(KeyboardKey key) const -> bool {
	const auto it = _keys.find(key);
	if (it == _keys.end()) {
		return false;
	}
	return it->second.get();
}

auto Keyboard::is_up(KeyboardKey key) const -> bool {
	const auto it = _keys.find(key);
	if (it == _keys.end()) {
		return true;
	}
	return !it->second.get();
}

auto Keyboard::is_pressed(KeyboardKey key) const -> bool {
	const auto it = _keys.find(key);
	if (it == _keys.end()) {
		return false;
	}
	return it->second.entered(true);
}

void Keyboard::update() {
	for (auto& [_, key] : _keys) {
		key.set_previous(key.get());
	}
}

void Keyboard::set_key(KeyboardKey key, bool state) {
	_keys[key].set_current(state);
}

} // namespace void_engine::display::window::input
