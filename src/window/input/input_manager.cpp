module void_engine.window;

namespace void_engine::window::input {

input_manager::input_manager(window& window) : keyboard_{window}, mouse_{window} {}

void input_manager::update() {
	keyboard_.update();
	mouse_.update();
}

auto input_manager::keyboard() -> class keyboard& {
	return keyboard_;
}

auto input_manager::mouse() -> class mouse& {
	return mouse_;
}

} // namespace void_engine::window::input
