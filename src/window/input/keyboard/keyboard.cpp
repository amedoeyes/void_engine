module void_engine.window;

import std;

namespace void_engine::window::input {

keyboard::keyboard(window& window) : window_{window} {
	key_listener_id_ = window_.get().events().add_listener<event::keyboard_key>([&](const auto& event) {
		set_key(event.key, event.action == keyboard_action::press || event.action == keyboard_action::repeat);
	});
}

keyboard::~keyboard() { window_.get().events().remove_listener<event::keyboard_key>(key_listener_id_); }

void keyboard::update() {
	for (auto& key : keys_) key.set_previous(key.get());
}

void keyboard::set_key(keyboard_key key, bool state) { keys_.at(std::to_underlying(key)).set_current(state); }

auto keyboard::is_down(keyboard_key key) const -> bool { return keys_.at(std::to_underlying(key)).get(); }

auto keyboard::is_up(keyboard_key key) const -> bool { return !keys_.at(std::to_underlying(key)).get(); }

auto keyboard::is_pressed(keyboard_key key) const -> bool { return keys_.at(std::to_underlying(key)).entered(true); }

auto keyboard::is_released(keyboard_key key) const -> bool { return keys_.at(std::to_underlying(key)).exited(true); }

} // namespace void_engine::window::input
