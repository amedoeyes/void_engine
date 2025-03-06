export module void_engine.utility.timer;

import std;

export namespace void_engine::utility {

class timer {
	using clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::time_point<clock>;
	using duration = std::chrono::duration<float>;

public:
	timer(const timer&) = default;
	timer(timer&&) = default;
	auto operator=(const timer&) -> timer& = default;
	auto operator=(timer&&) -> timer& = default;
	timer();
	~timer() = default;

	void reset();
	void start();
	void stop();

	[[nodiscard]]
	auto elapsed() const -> float;
	[[nodiscard]]
	auto is_running() const -> bool;

private:
	time_point _start;
	time_point _end;
	bool _is_running = false;
};

} // namespace void_engine::utility
