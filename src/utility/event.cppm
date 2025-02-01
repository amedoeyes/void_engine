module;

#include <cassert>

export module void_engine.utility.event;

import std;

export namespace void_engine::utility::event {

using EventListenerID = std::uint16_t;

template<typename... Args>
class EventManager {
public:
	template<typename T>
	using EventListener = std::function<void(const T&)>;
	using Event = std::variant<Args...>;
	using EventListeners = std::vector<std::pair<EventListenerID, std::function<void(const Event&)>>>;
	using Events = std::array<EventListeners, std::variant_size_v<Event>>;
	using EventIndex = std::uint16_t;
	using EventQueue = std::queue<std::pair<EventIndex, Event>>;

	EventManager(const EventManager&) = default;
	EventManager(EventManager&&) = default;
	auto operator=(const EventManager&) -> EventManager& = default;
	auto operator=(EventManager&&) -> EventManager& = default;
	EventManager() = default;
	~EventManager() = default;

	template<typename T>
	auto add_listener(EventListener<T>&& listener) -> EventListenerID {
		static constexpr EventIndex index = get_index<T>::value;
		auto& event = _events[index];
		EventListenerID id = _next_listener_id++;
		event.emplace_back(id, ([listener = std::move(listener)](const Event& event) { listener(std::get<T>(event)); }));
		return id;
	}

	template<typename T>
	void remove_listener(EventListenerID id) {
		static constexpr EventIndex index = get_index<T>::value;
		auto& event = _events[index];
		const auto it = std::ranges::find_if(event, [id](const auto& pair) { return id == pair.first; });
		assert(it != event.end() && "Listener does not exist");
		std::iter_swap(it, event.end() - 1);
		event.pop_back();
	}

	template<typename T>
	void emit(T&& data) {
		static constexpr EventIndex index = get_index<T>::value;
		_queue.emplace(index, std::forward<T>(data));
	}

	template<typename T>
	void emit() {
		static constexpr EventIndex index = get_index<T>::value;
		_queue.emplace(index, T{});
	}

	template<typename T>
	void clear() {
		static constexpr EventIndex index = get_index<T>::value;
		_events[index].clear();
	}

	void poll() {
		while (!_queue.empty()) {
			const auto [index, event] = std::move(_queue.front());
			_queue.pop();
			for (const auto& [_, listener] : _events[index]) {
				listener(event);
			}
		}
	}

private:
	Events _events;
	EventQueue _queue;
	EventListenerID _next_listener_id = 0;

	template<typename T>
	struct get_index
		: std::integral_constant<EventIndex, std::variant<std::type_identity<Args>...>(std::type_identity<T>()).index()> {};
};

} // namespace void_engine::utility::event
