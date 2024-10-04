#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_EVENT_HANDLER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_EVENT_HANDLER_HPP

#include "void_engine/display/window/event/drop_event.hpp"
#include "void_engine/display/window/event/framebuffer_size_event.hpp"
#include "void_engine/display/window/event/keyboard_char_event.hpp"
#include "void_engine/display/window/event/keyboard_char_mods_event.hpp"
#include "void_engine/display/window/event/keyboard_key_event.hpp"
#include "void_engine/display/window/event/mouse_button_event.hpp"
#include "void_engine/display/window/event/mouse_enter_event.hpp"
#include "void_engine/display/window/event/mouse_position_event.hpp"
#include "void_engine/display/window/event/mouse_scroll_event.hpp"
#include "void_engine/display/window/event/window_close_event.hpp"
#include "void_engine/display/window/event/window_content_scale_event.hpp"
#include "void_engine/display/window/event/window_focus_event.hpp"
#include "void_engine/display/window/event/window_iconify_event.hpp"
#include "void_engine/display/window/event/window_maximize_event.hpp"
#include "void_engine/display/window/event/window_position_event.hpp"
#include "void_engine/display/window/event/window_refresh_event.hpp"
#include "void_engine/display/window/event/window_size_event.hpp"
#include "void_engine/utility/event.hpp"

namespace void_engine::display::window {

class Window;

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

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_EVENT_HANDLER_HPP
