#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP

#include "void_engine/display/window/input/keyboard.hpp"
#include "void_engine/display/window/input/mouse.hpp"
#include "void_engine/utility/event/event_listener.hpp"

namespace void_engine::display::window {

namespace event {
struct KeyboardKeyEvent;
struct MouseButtonEvent;
struct MousePositionEvent;
struct MouseScrollEvent;
} // namespace event

class Window;

class WindowInputHandler {
public:
	WindowInputHandler(const WindowInputHandler&) = default;
	WindowInputHandler(WindowInputHandler&&) = delete;
	auto operator=(const WindowInputHandler&) -> WindowInputHandler& = default;
	auto operator=(WindowInputHandler&&) -> WindowInputHandler& = delete;
	explicit WindowInputHandler(Window& window);
	~WindowInputHandler();

	void update();

	[[nodiscard]] auto get_keyboard() -> input::Keyboard&;
	[[nodiscard]] auto get_mouse() -> input::Mouse&;

private:
	Window* _window;
	input::Keyboard* _keyboard;
	input::Mouse* _mouse;
	utility::event::EventListener<event::KeyboardKeyEvent>* _keyboard_key_listener;
	utility::event::EventListener<event::MouseButtonEvent>* _mouse_button_listener;
	utility::event::EventListener<event::MousePositionEvent>* _mouse_position_listener;
	utility::event::EventListener<event::MouseScrollEvent>* _mouse_scroll_listener;
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP
