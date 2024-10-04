#ifndef VOID_ENGINE_DISPLAY_WINDOW_INPUT_KEYBOARD_KEYBOARD_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_INPUT_KEYBOARD_KEYBOARD_HPP

#include "void_engine/display/window/input/keyboard/enums.hpp"
#include "void_engine/utility/event.hpp"
#include "void_engine/utility/state.hpp"

#include <array>

namespace void_engine::display::window {

class WindowInputHandler;
class Window;

namespace input::keyboard {

class Keyboard {
	friend class window::WindowInputHandler;

public:
	Keyboard(const Keyboard&) = default;
	Keyboard(Keyboard&&) = default;
	auto operator=(const Keyboard&) -> Keyboard& = default;
	auto operator=(Keyboard&&) -> Keyboard& = default;
	explicit Keyboard(Window& window);
	~Keyboard();

	void update();

	void set_key(Key key, bool state);

	[[nodiscard]] auto is_down(Key key) const -> bool;
	[[nodiscard]] auto is_up(Key key) const -> bool;
	[[nodiscard]] auto is_pressed(Key key) const -> bool;
	[[nodiscard]] auto is_released(Key key) const -> bool;

private:
	Window* _window;
	std::array<utility::State<bool>, 512> _keys;
	utility::event::EventListenerID _keyboard_key_listener;
};

} // namespace input::keyboard

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_INPUT_KEYBOARD_KEYBOARD_HPP
