module;

#include <GLFW/glfw3.h>

export module void_engine.window:window_event_handler;

import :window_events;

import void_engine.utility.event;

export namespace void_engine::window {
class window;
} // namespace void_engine::window

export namespace void_engine::window {

class window_event_handler final : public utility::event::EventManager<event::drop,
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
	window_event_handler(const window_event_handler&) = delete;
	window_event_handler(window_event_handler&&) = default;
	auto operator=(const window_event_handler&) -> window_event_handler& = delete;
	auto operator=(window_event_handler&&) -> window_event_handler& = default;
	window_event_handler() = delete;
	explicit window_event_handler(const window& window);
	~window_event_handler();

private:
	GLFWwindow* window_;
};

} // namespace void_engine::window
