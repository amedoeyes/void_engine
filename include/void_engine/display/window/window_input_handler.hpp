#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP

#include "void_engine/display/window/inputs/keyboard.hpp"
#include "void_engine/display/window/inputs/mouse.hpp"

namespace void_engine {

namespace event {
template <typename T>
class EventListener;
} // namespace event

namespace display::window {

namespace events {
struct KeyboardKeyEvent;
struct MouseButtonEvent;
struct MousePositionEvent;
struct MouseScrollEvent;
} // namespace events

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

	[[nodiscard]] auto get_keyboard() -> inputs::Keyboard&;
	[[nodiscard]] auto get_mouse() -> inputs::Mouse&;

private:
	Window* _window;
	inputs::Keyboard* _keyboard;
	inputs::Mouse* _mouse;
	event::EventListener<events::KeyboardKeyEvent>* _keyboard_key_listener;
	event::EventListener<events::MouseButtonEvent>* _mouse_button_listener;
	event::EventListener<events::MousePositionEvent>* _mouse_position_listener;
	event::EventListener<events::MouseScrollEvent>* _mouse_scroll_listener;
};

} // namespace display::window

} // namespace void_engine

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_INPUT_HANDLER_HPP
