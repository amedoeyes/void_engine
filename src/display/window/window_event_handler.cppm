module;

#include "void_engine/utility/event.hpp"

export module void_engine.display.window:window_event_handler;

import :window;
import :window_events;

export namespace void_engine::display::window {

class WindowEventHandler final
	: public utility::event::EventManager<
			event::DropEvent, event::FramebufferSizeEvent, event::KeyboardCharEvent,
			event::KeyboardCharModsEvent, event::KeyboardKeyEvent, event::MouseButtonEvent,
			event::MouseEnterEvent, event::MousePositionEvent, event::MouseScrollEvent,
			event::WindowCloseEvent, event::WindowContentScaleEvent, event::WindowFocusEvent,
			event::WindowIconifyEvent, event::WindowMaximizeEvent, event::WindowPositionEvent,
			event::WindowRefreshEvent, event::WindowSizeEvent> {
public:
	WindowEventHandler(const WindowEventHandler&) = default;
	WindowEventHandler(WindowEventHandler&&) = delete;
	auto operator=(const WindowEventHandler&) -> WindowEventHandler& = default;
	auto operator=(WindowEventHandler&&) -> WindowEventHandler& = delete;
	explicit WindowEventHandler(Window& window);
	~WindowEventHandler();

private:
	Window* _window;
};

} // namespace void_engine::display::window
