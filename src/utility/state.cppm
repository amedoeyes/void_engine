export module void_engine.utility.state;

import std;

export namespace void_engine::utility {

template<typename T>
class State {
public:
	State(const State& other) : _current(other._current), _previous(other._previous) {}

	State(State&& other) noexcept : _current(std::move(other._current)), _previous(std::move(other._previous)) {}

	auto operator=(const State& other) -> State& {
		if (this != &other) {
			_current = other._current;
			_previous = other._previous;
		}
		return *this;
	}

	auto operator=(State&& other) noexcept -> State& {
		if (this != &other) {
			_current = std::move(other._current);
			_previous = std::move(other._previous);
		}
		return *this;
	}

	State() : _current(), _previous() {}

	explicit State(T initial_state) : _current(initial_state), _previous(initial_state) {}

	~State() = default;

	void set(T state) {
		_previous = _current;
		_current = state;
	}

	void set_current(T state) { _current = state; }

	void set_previous(T state) { _previous = state; }

	[[nodiscard]]
	auto get() const -> T {
		return _current;
	}

	[[nodiscard]]
	auto get_previous() const -> T {
		return _previous;
	}

	[[nodiscard]]
	auto is(T state) const -> bool {
		return _current == state;
	}

	[[nodiscard]]
	auto changed() const -> bool {
		return _previous != _current;
	}

	[[nodiscard]]
	auto entered(T state) const -> bool {
		return _previous != state && _current == state;
	}

	[[nodiscard]]
	auto exited(T state) const -> bool {
		return _previous == state && _current != state;
	}

	auto operator=(T state) -> State& {
		_previous = _current;
		_current = state;
		return *this;
	}

	explicit operator T() const { return _current; }

	auto operator==(T state) const -> bool { return _current == state; }

	auto operator!=(T state) const -> bool { return _current != state; }

private:
	T _current{};
	T _previous{};
};

} // namespace void_engine::utility
