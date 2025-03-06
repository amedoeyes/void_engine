export module void_engine.window:window_inputs;

import :input.keyboard;
import :input.mouse;

export namespace void_engine::window {

struct window_inputs {
	input::keyboard keyboard;
	input::mouse mouse;

	auto update() {
		keyboard.update();
		mouse.update();
	}
};

}  // namespace void_engine::window
