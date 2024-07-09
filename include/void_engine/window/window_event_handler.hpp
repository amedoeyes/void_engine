#ifndef VOID_ENGINE_WINDOW_WINDOW_EVENT_HANDLER_HPP
#define VOID_ENGINE_WINDOW_WINDOW_EVENT_HANDLER_HPP

#include "void_engine/event/event_listener.hpp"
#include "void_engine/event/event_manager.hpp"
#include "void_engine/window/events/drop_event.hpp"
#include "void_engine/window/events/framebuffer_size_event.hpp"
#include "void_engine/window/events/keyboard_char_event.hpp"
#include "void_engine/window/events/keyboard_char_mods_event.hpp"
#include "void_engine/window/events/keyboard_key_event.hpp"
#include "void_engine/window/events/mouse_button_event.hpp"
#include "void_engine/window/events/mouse_enter_event.hpp"
#include "void_engine/window/events/mouse_position_event.hpp"
#include "void_engine/window/events/mouse_scroll_event.hpp"
#include "void_engine/window/events/window_close_event.hpp"
#include "void_engine/window/events/window_content_scale_event.hpp"
#include "void_engine/window/events/window_focus_event.hpp"
#include "void_engine/window/events/window_iconify_event.hpp"
#include "void_engine/window/events/window_maximize_event.hpp"
#include "void_engine/window/events/window_position_event.hpp"
#include "void_engine/window/events/window_refresh_event.hpp"
#include "void_engine/window/events/window_size_event.hpp"

#include <glm/ext/vector_float2.hpp>

namespace void_engine::window {

class Window;

class WindowEventHandler {
public:
	WindowEventHandler(Window* window);
	~WindowEventHandler();

	template <typename EventType>
	auto add_listener(event::EventListener<EventType>::Callback&& callback)
		-> event::EventListener<EventType>* {
		return _event_manager.add_listener<EventType>(std::move(callback));
	}

	template <typename EventType>
	void remove_listener(const event::EventListener<EventType>* listener) {
		_event_manager.remove_listener<EventType>(listener);
	}

	template <typename EventType, typename... Args>
	void emit(Args&&... args) {
		_event_manager.emit<EventType>(std::forward<Args>(args)...);
	}

	void poll();

private:
	Window* _window;
	event::EventManager _event_manager;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_EVENT_HANDLER_HPP
