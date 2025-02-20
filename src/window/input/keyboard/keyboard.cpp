module void_engine.window;

import std;

namespace void_engine::window::input {

auto keyboard::update() -> void {
	for (auto& key : keys_) key.set_previous(key.current());
}

auto keyboard::set_key(keyboard_key key, bool state) -> void {
	keys_.at(std::to_underlying(key)).set_current(state);
}

auto keyboard::is_down(keyboard_key key) const -> bool {
	return keys_.at(std::to_underlying(key)).current();
}

auto keyboard::is_up(keyboard_key key) const -> bool {
	return !keys_.at(std::to_underlying(key)).current();
}

auto keyboard::is_pressed(keyboard_key key) const -> bool {
	return keys_.at(std::to_underlying(key)).entered(true);
}

auto keyboard::is_released(keyboard_key key) const -> bool {
	return keys_.at(std::to_underlying(key)).exited(true);
}

} // namespace void_engine::window::input
