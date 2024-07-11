#ifndef VOID_ENGINE_EVENT_EVENT_LISTENER_BASE_HPP
#define VOID_ENGINE_EVENT_EVENT_LISTENER_BASE_HPP

#include "void_engine/event/event_base.hpp"

namespace void_engine::event {

class EventListenerBase {
public:
	EventListenerBase(const EventListenerBase&) = default;
	EventListenerBase(EventListenerBase&&) = delete;
	auto operator=(const EventListenerBase&) -> EventListenerBase& = default;
	auto operator=(EventListenerBase&&) -> EventListenerBase& = delete;
	EventListenerBase() = default;
	virtual ~EventListenerBase() = default;
	virtual void emit(const EventBase* event) const = 0;
};

} // namespace void_engine::event

#endif // !VOID_ENGINE_EVENT_EVENT_LISTENER_BASE_HPP
