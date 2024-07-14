#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_EVENT_HANDLER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_EVENT_HANDLER_HPP

#include "void_engine/event/event_manager.hpp"

namespace void_engine::display::window {

class Window;

class WindowEventHandler final : public ::void_engine::event::EventManager {
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

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_EVENT_HANDLER_HPP
