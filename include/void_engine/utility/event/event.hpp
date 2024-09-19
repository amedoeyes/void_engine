#ifndef VOID_ENGINE_UTILITY_EVENT_EVENT_HPP
#define VOID_ENGINE_UTILITY_EVENT_EVENT_HPP

#include "void_engine/utility/event/event_base.hpp"

#include <utility>

namespace void_engine::utility::event {

template <typename EventType>
class Event : public EventBase {
public:
	Event(const Event&) = delete;
	Event(Event&&) = delete;
	auto operator=(const Event&) -> Event& = delete;
	auto operator=(Event&&) -> Event& = delete;
	Event() = default;
	explicit Event(EventType&& data) : _data(std::move(data)) {
	}
	~Event() override = default;

	auto get_data() const -> const EventType& {
		return _data;
	}

private:
	EventType _data;
};

} // namespace void_engine::utility::event

#endif // !VOID_ENGINE_UTILITY_EVENT_EVENT_HPP
