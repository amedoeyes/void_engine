#ifndef VOID_ENGINE_EVENT_EVENT_HPP
#define VOID_ENGINE_EVENT_EVENT_HPP

#include "void_engine/event/event_base.hpp"

namespace void_engine::event {

template <typename EventType>
class Event : public EventBase {
public:
	Event(const EventType& data) : _data(data) {
	}

	auto get_data() const -> const EventType& {
		return _data;
	}

private:
	EventType _data;
};

} // namespace void_engine::event

#endif // !VOID_ENGINE_EVENT_EVENT_HPP
