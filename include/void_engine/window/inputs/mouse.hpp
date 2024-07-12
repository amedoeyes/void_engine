#ifndef VOID_ENGINE_WINDOW_INPUTS_MOUSE_HPP
#define VOID_ENGINE_WINDOW_INPUTS_MOUSE_HPP

#include "void_engine/window/inputs/input_state.hpp"

#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <unordered_map>

namespace void_engine::window {

class WindowInputHandler;

namespace inputs {

enum class MouseButton : std::uint8_t {
	left = 0,
	right = 1,
	middle = 2
};

class Mouse {
	friend class void_engine::window::WindowInputHandler;

public:
	[[nodiscard]] auto is_down(MouseButton button) const -> bool;
	[[nodiscard]] auto is_up(MouseButton button) const -> bool;
	[[nodiscard]] auto is_pressed(MouseButton button) const -> bool;
	[[nodiscard]] auto get_position() const -> glm::vec2;
	[[nodiscard]] auto get_delta_position() const -> glm::vec2;
	[[nodiscard]] auto get_scroll() const -> glm::vec2;

private:
	std::unordered_map<MouseButton, InputState<bool>> _buttons;
	InputState<glm::vec2> _position;
	glm::vec2 _scroll = glm::vec2(0.f);

	void update();
	void set_button(MouseButton button, bool state);
	void set_position(const glm::vec2& position);
	void set_scroll(const glm::vec2& scroll);
};

} // namespace inputs

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_INPUTS_MOUSE_HPP
