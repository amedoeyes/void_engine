#ifndef VOID_ENGINE_EVENT_EVENT_LISTENER_HPP
#define VOID_ENGINE_EVENT_EVENT_LISTENER_HPP

#include "void_engine/event/event.hpp"
#include "void_engine/event/event_base.hpp"
#include "void_engine/event/event_listener_base.hpp"

#include <functional>

namespace void_engine::event {

template <typename EventType>
class EventListener : public EventListenerBase {
public:
	using Callback = std::function<void(const EventType&)>;

	EventListener(Callback&& callback) : _callback(std::move(callback)) {
	}

	void emit(const EventBase* event) const override {
		if (_callback == nullptr) return;
		_callback(static_cast<const Event<EventType>*>(event)->get_data());
	}

private:
	Callback _callback;
};

} // namespace void_engine::event

#endif // !VOID_ENGINE_EVENT_EVENT_LISTENER_HPP
