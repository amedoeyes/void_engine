module;

#include <GLFW/glfw3.h>

export module void_engine.window:window_event_bus;

import :window_events;

import void_engine.utility.event_bus;

export namespace void_engine::window {
class window;
} // namespace void_engine::window

export namespace void_engine::window {

class window_event_bus final : public utility::event_bus<event::drop,
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
	window_event_bus(const window_event_bus&) = delete;
	window_event_bus(window_event_bus&&) = default;
	auto operator=(const window_event_bus&) -> window_event_bus& = delete;
	auto operator=(window_event_bus&&) -> window_event_bus& = default;
	explicit window_event_bus(const window& window);
	~window_event_bus();

private:
	GLFWwindow* window_;
};

} // namespace void_engine::window
