export module void_engine.utility.state;

import std;

export namespace void_engine::utility {

template<typename T>
class state {
public:
	state() = default;

	explicit state(const T& initial_state) : current_{initial_state}, previous_{initial_state} {}

	auto set(const T& state) -> void {
		previous_ = current_;
		current_ = state;
	}

	auto set_current(const T& state) -> void {
		current_ = state;
	}

	auto set_previous(const T& state) -> void {
		previous_ = state;
	}

	[[nodiscard]]
	auto current() const -> const T& {
		return current_;
	}

	[[nodiscard]]
	auto previous() const -> const T& {
		return previous_;
	}

	[[nodiscard]]
	auto is(const T& state) const -> bool {
		return current_ == state;
	}

	[[nodiscard]]
	auto changed() const -> bool {
		return previous_ != current_;
	}

	[[nodiscard]]
	auto entered(const T& state) const -> bool {
		return previous_ != state && current_ == state;
	}

	[[nodiscard]]
	auto exited(T state) const -> bool {
		return previous_ == state && current_ != state;
	}

	auto operator=(const T& state) -> class state& {
		previous_ = current_;
		current_ = state;
		return *this;
	}

	explicit operator T() const {
		return current_;
	}

	auto operator==(const T& state) const -> bool {
		return current_ == state;
	}

	auto operator!=(const T& state) const -> bool {
		return current_ != state;
	}

private:
	T current_{};
	T previous_{};
};

} // namespace void_engine::utility
