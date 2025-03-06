export module void_engine.utility.event_bus;

import std;

export namespace void_engine::utility {

template<typename... Args>
class event_bus {
public:
	using event_type = std::variant<Args...>;
	using index_type = std::uint32_t;
	using listener_type = std::function<void(const event_type&)>;
	using id_type = std::uint32_t;

	template<typename T>
	auto add_listener(std::function<void(const T&)>&& listener) -> id_type {
		static constexpr auto index = get_index<T>::value;
		auto& event = _events[index];
		const auto id = _next_id++;
		event.emplace_back(id, ([listener = std::move(listener)](const auto& event) { listener(std::get<T>(event)); }));
		return id;
	}

	template<typename T>
	auto remove_listener(id_type id) -> void {
		static constexpr auto index = get_index<T>::value;
		auto& event = _events[index];
		const auto it = std::ranges::find_if(event, [&](const auto& pair) { return id == pair.first; });
		if (it == event.end()) return;
		event.erase(it);
	}

	template<typename T>
	void emit(T&& data) {
		static constexpr auto index = get_index<T>::value;
		_queue.emplace(index, std::forward<T>(data));
	}

	template<typename T>
	void emit() {
		static constexpr auto index = get_index<T>::value;
		_queue.emplace(index, T{});
	}

	template<typename T>
	void clear() {
		static constexpr auto index = get_index<T>::value;
		_events[index].clear();
	}

	void poll() {
		while (!_queue.empty()) {
			const auto& [index, event] = _queue.front();
			for (const auto& [_, listener] : _events[index]) listener(event);
			_queue.pop();
		}
	}

private:
	std::array<std::vector<std::pair<id_type, listener_type>>, std::variant_size_v<event_type>> _events;
	std::queue<std::pair<index_type, event_type>> _queue;
	id_type _next_id = 0;

	template<typename T>
	struct get_index
		: std::integral_constant<index_type, std::variant<std::type_identity<Args>...>(std::type_identity<T>()).index()> {};
};

} // namespace void_engine::utility
