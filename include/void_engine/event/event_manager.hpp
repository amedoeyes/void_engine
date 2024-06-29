#ifndef VOID_ENGINE_EVENT_EVENT_MANAGER_HPP
#define VOID_ENGINE_EVENT_EVENT_MANAGER_HPP

#include "void_engine/event/event_base.hpp"
#include "void_engine/event/event_listener.hpp"
#include "void_engine/event/event_listener_base.hpp"
#include "void_engine/event/types.hpp"

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace void_engine::event {

class EventManager {
public:
	~EventManager() {
		for (const auto& [_, listeners] : _listeners) {
			for (const auto& listener : listeners) {
				delete listener;
			}
		}
	}

	template <typename EventType>
	auto add_listener(const Callback<EventType>& callback)
		-> EventListener<EventType>* {
		const EventID id = get_event_id<EventType>();
		auto* listener = new EventListener<EventType>(callback);
		_listeners[id].push_back(listener);
		return listener;
	}

	template <typename EventType>
	void remove_listener(const EventListener<EventType>* listener) {
		const EventID id = get_event_id<EventType>();
		const auto listeners_it = _listeners.find(id);
		if (listeners_it == _listeners.end()) {
			throw std::runtime_error("Could not find listeners");
		}
		auto& listeners = listeners_it->second;
		const auto listener_it =
			std::find(listeners.begin(), listeners.end(), listener);
		if (listener_it == listeners.end()) {
			throw std::runtime_error("Could not find listener");
		}
		listeners.erase(listener_it);
		delete listener;
	}

	template <typename EventType, typename... Args>
	void emit(Args&&... args) {
		const EventID id = get_event_id<EventType>();
		const auto* event = new Event<EventType>({std::forward<Args>(args)...});
		_queue.push({id, event});
	}

	template <typename EventType>
	void remove() {
		const EventID id = get_event_id<EventType>();
		const auto it = _listeners.find(id);
		if (it != _listeners.end()) {
			for (const auto& listener : it->second) {
				delete listener;
			}
			_listeners.erase(it);
		}
	}

	void poll() {
		while (!_queue.empty()) {
			const auto [id, event] = _queue.front();
			const auto it = _listeners.find(id);
			if (it != _listeners.end()) {
				for (const auto& listener : it->second) {
					listener->emit(event);
				}
			}
			delete event;
			_queue.pop();
		}
	}

private:
	EventID _next_id = 0;
	std::unordered_map<EventID, std::vector<EventListenerBase*>> _listeners;
	std::queue<std::pair<EventID, const EventBase*>> _queue;

	template <typename Event>
	auto get_event_id() -> EventID {
		static const EventID id = _next_id++;
		return id;
	}
};

} // namespace void_engine::event

#endif // !VOID_ENGINE_EVENT_EVENT_MANAGER_HPP
