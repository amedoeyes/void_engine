export module void_engine.window:input.keyboard;

import :input.keyboard_enums;
import :window_event_bus;

import std;
import void_engine.utility.state;

export namespace void_engine::window {
class window;
}  // namespace void_engine::window

export namespace void_engine::window::input {

class keyboard {
public:
	keyboard(const keyboard&) = delete;
	keyboard(keyboard&&) = default;
	auto operator=(const keyboard&) -> keyboard& = delete;
	auto operator=(keyboard&&) -> keyboard& = default;
	keyboard() = delete;
	explicit keyboard(window& window);
	~keyboard();

	auto update() -> void;

	auto set_key(keyboard_key key, bool state) -> void;

	[[nodiscard]]
	auto is_down(keyboard_key key) const -> bool;

	[[nodiscard]]
	auto is_up(keyboard_key key) const -> bool;

	[[nodiscard]]
	auto is_pressed(keyboard_key key) const -> bool;

	[[nodiscard]]
	auto is_released(keyboard_key key) const -> bool;

private:
	std::reference_wrapper<window> window_;
	std::array<utility::State<bool>, 512> keys_;
	window_event_bus::id_type key_listener_id_;
};

} // namespace void_engine::window::input
