#include "void_engine/utility/timer.hpp"

namespace void_engine::utility {

Timer::Timer() : _start(Clock::now()), _end(Clock::now()) {
}

void Timer::reset() {
	_start = Clock::now();
	_end = Clock::now();
	_is_running = false;
}

void Timer::start() {
	if (!_is_running) {
		_start = Clock::now() - (_end - _start);
		_is_running = true;
	}
}

void Timer::stop() {
	if (_is_running) {
		_end = Clock::now();
		_is_running = false;
	}
}

auto Timer::get_elapsed() const -> float {
	if (_is_running) {
		return Duration(Clock::now() - _start).count();
	}
	return Duration(_end - _start).count();
}

auto Timer::is_running() const -> bool {
	return _is_running;
}

} // namespace void_engine::utility
