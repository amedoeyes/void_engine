#include "void_engine/display/window/inputs/keyboard.hpp"

namespace void_engine::display::window::inputs {

auto Keyboard::is_down(KeyboardKey key) const -> bool {
	const auto it = _keys.find(key);
	if (it == _keys.end()) {
		return false;
	}
	return it->second.current;
}

auto Keyboard::is_up(KeyboardKey key) const -> bool {
	const auto it = _keys.find(key);
	if (it == _keys.end()) {
		return true;
	}
	return !it->second.current;
}

auto Keyboard::is_pressed(KeyboardKey key) const -> bool {
	const auto it = _keys.find(key);
	if (it == _keys.end()) {
		return false;
	}
	return it->second.current && !it->second.previous;
}

void Keyboard::update() {
	for (auto& [_, key] : _keys) {
		key.previous = key.current;
	}
}

void Keyboard::set_key(KeyboardKey key, bool state) {
	_keys[key].current = state;
}

} // namespace void_engine::display::window::inputs
