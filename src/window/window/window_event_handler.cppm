export module void_engine.window:window_event_handler;

import :window_events;

import void_engine.utility.event;

export namespace void_engine::window {
class window;
}  // namespace void_engine::window

export namespace void_engine::window {

class WindowEventHandler final : public utility::event::EventManager<event::drop,
                                                                     event::framebuffer_size,
                                                                     event::keyboard_char,
                                                                     event::keyboard_char_mods,
                                                                     event::keyboard_key,
                                                                     event::mouse_button,
                                                                     event::mouse_enter,
                                                                     event::mouse_position,
                                                                     event::mouse_scroll,
                                                                     event::window_close,
                                                                     event::window_content_scale,
                                                                     event::window_focus,
                                                                     event::window_iconify,
                                                                     event::window_maximize,
                                                                     event::window_position,
                                                                     event::window_refresh,
                                                                     event::window_size> {
public:
	WindowEventHandler(const WindowEventHandler&) = default;
	WindowEventHandler(WindowEventHandler&&) = delete;
	auto operator=(const WindowEventHandler&) -> WindowEventHandler& = default;
	auto operator=(WindowEventHandler&&) -> WindowEventHandler& = delete;
	explicit WindowEventHandler(window& window);
	~WindowEventHandler();

private:
	window* _window;
};

} // namespace void_engine::window
