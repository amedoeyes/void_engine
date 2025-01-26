export module void_engine.utility.timer;

import std;

export namespace void_engine::utility {

class Timer {
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	using Duration = std::chrono::duration<float>;

public:
	Timer(const Timer&) = default;
	Timer(Timer&&) = default;
	auto operator=(const Timer&) -> Timer& = default;
	auto operator=(Timer&&) -> Timer& = default;
	Timer();
	~Timer() = default;

	void reset();
	void start();
	void stop();

	[[nodiscard]] auto get_elapsed() const -> float;
	[[nodiscard]] auto is_running() const -> bool;

private:
	TimePoint _start;
	TimePoint _end;
	bool _is_running = false;
};

} // namespace void_engine::utility
