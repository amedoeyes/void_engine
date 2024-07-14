#ifndef VOID_ENGINE_DISPLAY_WINDOW_INPUTS_INPUT_STATE_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_INPUTS_INPUT_STATE_HPP

namespace void_engine::display::window::inputs {

template <typename T>
struct InputState {
	T current{};
	T previous{};
};

} // namespace void_engine::display::window::inputs

#endif // !VOID_ENGINE_DISPLAY_WINDOW_INPUTS_INPUT_STATE_HPP
