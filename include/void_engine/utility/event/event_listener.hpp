#ifndef VOID_ENGINE_UTILITY_EVENT_EVENT_LISTENER_HPP
#define VOID_ENGINE_UTILITY_EVENT_EVENT_LISTENER_HPP

#include "void_engine/utility/event/event.hpp"
#include "void_engine/utility/event/event_base.hpp"
#include "void_engine/utility/event/event_listener_base.hpp"

#include <functional>

namespace void_engine::utility::event {

template <typename EventType>
class EventListener : public EventListenerBase {
public:
	using Callback = std::function<void(const EventType&)>;

	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	auto operator=(const EventListener&) -> EventListener& = delete;
	auto operator=(EventListener&&) -> EventListener& = delete;
	explicit EventListener(Callback&& callback) : _callback(std::move(callback)) {
	}
	~EventListener() override = default;

	void emit(const EventBase* event) const override {
		if (_callback == nullptr) {
			return;
		}
		_callback(static_cast<const Event<EventType>*>(event)->get_data());
	}

private:
	Callback _callback;
};

} // namespace void_engine::utility::event

#endif // !VOID_ENGINE_UTILITY_EVENT_EVENT_LISTENER_HPP
