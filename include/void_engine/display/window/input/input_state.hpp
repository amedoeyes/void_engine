#ifndef VOID_ENGINE_DISPLAY_WINDOW_INPUT_INPUT_STATE_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_INPUT_INPUT_STATE_HPP

namespace void_engine::display::window::input {

template <typename T>
struct InputState {
	T current{};
	T previous{};
};

} // namespace void_engine::display::window::input

#endif // !VOID_ENGINE_DISPLAY_WINDOW_INPUT_INPUT_STATE_HPP
