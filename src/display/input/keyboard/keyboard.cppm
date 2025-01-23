module;

#include "void_engine/utility/state.hpp"

export module void_engine.display:input.keyboard;

import :input.keyboard.enums;
import :window.window;

import std;
import void_engine.utility.event;

export namespace void_engine::display::input::keyboard {

class Keyboard {
public:
	Keyboard(const Keyboard&) = default;
	Keyboard(Keyboard&&) = default;
	auto operator=(const Keyboard&) -> Keyboard& = default;
	auto operator=(Keyboard&&) -> Keyboard& = default;
	explicit Keyboard(window::Window& window);
	~Keyboard();

	void update();

	void set_key(Key key, bool state);

	[[nodiscard]] auto is_down(Key key) const -> bool;
	[[nodiscard]] auto is_up(Key key) const -> bool;
	[[nodiscard]] auto is_pressed(Key key) const -> bool;
	[[nodiscard]] auto is_released(Key key) const -> bool;

private:
	window::Window* _window;
	std::array<utility::State<bool>, 512> _keys;
	utility::event::EventListenerID _keyboard_key_listener;
};

} // namespace void_engine::display::input::keyboard
