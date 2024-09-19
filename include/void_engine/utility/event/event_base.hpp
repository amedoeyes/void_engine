#ifndef VOID_ENGINE_UTILITY_EVENT_EVENT_BASE_HPP
#define VOID_ENGINE_UTILITY_EVENT_EVENT_BASE_HPP

namespace void_engine::utility::event {

class EventBase {
public:
	EventBase(const EventBase&) = delete;
	EventBase(EventBase&&) = delete;
	auto operator=(const EventBase&) -> EventBase& = delete;
	auto operator=(EventBase&&) -> EventBase& = delete;
	EventBase() = default;
	virtual ~EventBase() = default;
};

} // namespace void_engine::utility::event

#endif // !VOID_ENGINE_UTILITY_EVENT_EVENT_BASE_HPP
