#ifndef VOID_ENGINE_EVENT_EVENT_MANAGER_HPP
#define VOID_ENGINE_EVENT_EVENT_MANAGER_HPP

#include "void_engine/event/event.hpp"
#include "void_engine/event/event_base.hpp"
#include "void_engine/event/event_listener.hpp"
#include "void_engine/event/event_listener_base.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

namespace void_engine::event {

using EventID = uint32_t;

class EventManager {
public:
	EventManager(const EventManager&) = default;
	EventManager(EventManager&&) = delete;
	auto operator=(const EventManager&) -> EventManager& = default;
	auto operator=(EventManager&&) -> EventManager& = delete;
	EventManager() = default;
	~EventManager() {
		for (const auto& [_, listeners] : _listeners) {
			for (const auto& listener : listeners) {
				delete listener;
			}
		}
	}

	template <typename EventType>
	auto add_listener(EventListener<EventType>::Callback&& callback) -> EventListener<EventType>* {
		const EventID id = get_event_id<EventType>();
		auto* listener = new EventListener(std::move(callback));
		_listeners[id].push_back(listener);
		return listener;
	}

	template <typename EventType>
	void remove_listener(const EventListener<EventType>* listener) {
		const EventID id = get_event_id<EventType>();
		assert(_listeners.find(id) != _listeners.end() && "Event does not exist");
		const auto it = std::find(_listeners[id].begin(), _listeners[id].end(), listener);
		assert(it != _listeners[id].end() && "Listener does not exist");
		_listeners[id].erase(it);
		delete listener;
	}

	template <typename EventType>
	void emit(EventType&& data) {
		const EventID id = get_event_id<EventType>();
		auto* event = new Event<EventType>(std::forward<EventType>(data));
		_queue.push({id, event});
	}

	template <typename EventType>
	void emit() {
		const EventID id = get_event_id<EventType>();
		auto* event = new Event<EventType>();
		_queue.push({id, event});
	}

	template <typename EventType>
	void remove() {
		const EventID id = get_event_id<EventType>();
		assert(_listeners.find(id) != _listeners.end() && "Event does not exist");
		for (const auto& listener : _listeners[id]) {
			delete listener;
		}
		_listeners.erase(id);
	}

	void poll() {
		while (!_queue.empty()) {
			const auto [id, event] = _queue.front();
			for (const auto& listener : _listeners[id]) {
				listener->emit(event);
			}
			delete event;
			_queue.pop();
		}
	}

private:
	std::unordered_map<EventID, std::vector<EventListenerBase*>> _listeners;
	std::queue<std::pair<EventID, const EventBase*>> _queue;

	[[nodiscard]] static auto event_counter() -> EventID {
		static EventID counter = 0;
		return counter++;
	}

	template <typename Event>
	[[nodiscard]] auto get_event_id() const -> EventID {
		static const EventID id = event_counter();
		return id;
	}
};

} // namespace void_engine::event

#endif // !VOID_ENGINE_EVENT_EVENT_MANAGER_HPP
