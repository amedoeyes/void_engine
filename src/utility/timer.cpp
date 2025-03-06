module void_engine.utility.timer;

namespace void_engine::utility {

timer::timer() : _start(clock::now()), _end(clock::now()) {}

void timer::reset() {
	_start = clock::now();
	_end = clock::now();
	_is_running = false;
}

void timer::start() {
	if (!_is_running) {
		_start = clock::now() - (_end - _start);
		_is_running = true;
	}
}

void timer::stop() {
	if (_is_running) {
		_end = clock::now();
		_is_running = false;
	}
}

auto timer::elapsed() const -> float {
	if (_is_running) {
		return duration(clock::now() - _start).count();
	}
	return duration(_end - _start).count();
}

auto timer::is_running() const -> bool {
	return _is_running;
}

} // namespace void_engine::utility
