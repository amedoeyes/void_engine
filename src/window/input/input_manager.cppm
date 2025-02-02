export module void_engine.window:input.input_manager;

import :input.keyboard;
import :input.mouse;

export namespace void_engine::window {
class window;
}  // namespace void_engine::window

export namespace void_engine::window::input {

class input_manager {
public:
	input_manager() = delete;
	explicit input_manager(window& window);

	auto update() -> void;

	[[nodiscard]]
	auto keyboard() -> keyboard&;

	[[nodiscard]]
	auto mouse() -> mouse&;

private:
	class keyboard keyboard_;
	class mouse mouse_;
};

} // namespace void_engine::window::input
