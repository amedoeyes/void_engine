module;

#include <GLFW/glfw3.h>

export module void_engine.window:input.keyboard;

import :input.keyboard_enums;

import std;
import void_engine.utility.state;

export namespace void_engine::window::input {

class keyboard {
public:
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
	std::array<utility::state<bool>, 512> keys_;
};

} // namespace void_engine::window::input
