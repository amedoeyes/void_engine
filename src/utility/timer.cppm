export module void_engine.utility.timer;

import std;

export namespace void_engine::utility {

class Timer {
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	using Duration = std::chrono::duration<float>;

public:
	Timer() : _start(Clock::now()), _end(Clock::now()) {
	}

	void reset() {
		_start = Clock::now();
		_end = Clock::now();
		_is_running = false;
	}

	void start() {
		if (!_is_running) {
			_start = Clock::now() - (_end - _start);
			_is_running = true;
		}
	}

	void stop() {
		if (_is_running) {
			_end = Clock::now();
			_is_running = false;
		}
	}

	[[nodiscard]] auto get_elapsed() const -> float {
		if (_is_running) {
			return Duration(Clock::now() - _start).count();
		}
		return Duration(_end - _start).count();
	}

	[[nodiscard]] auto is_running() const -> bool {
		return _is_running;
	}

private:
	TimePoint _start;
	TimePoint _end;
	bool _is_running = false;
};

} // namespace void_engine::utility
