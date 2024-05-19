#ifndef VOID_ENGINE_INPUT_MOUSE_HPP
#define VOID_ENGINE_INPUT_MOUSE_HPP

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <unordered_map>

namespace void_engine::input {

enum class MouseButton {
	left = 0,
	right = 1,
	middle = 2
};

class Mouse {
	public:
	void update();

	bool is_button_down(MouseButton button) const;
	bool is_button_up(MouseButton button) const;
	bool is_button_pressed(MouseButton button) const;

	glm::vec2 get_position() const;
	void set_position(float x, float y);

	glm::vec2 get_scroll() const;
	void set_scroll(float x, float y);

	bool get_state(MouseButton button) const;
	void set_state(MouseButton button, bool state);

	bool get_prev_state(MouseButton button) const;
	void set_prev_state(MouseButton button, bool state);

	static void button_callback(
		GLFWwindow* window, int button, int action, [[maybe_unused]] int mods
	);
	static void position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(
		GLFWwindow* window, double xoffset, double yoffset
	);

	private:
	std::unordered_map<MouseButton, bool> _states;
	std::unordered_map<MouseButton, bool> _prev_states;
	glm::vec2 _position = {0.0f, 0.0f};
	glm::vec2 _scroll = {0.0f, 0.0f};
};

}  // namespace void_engine::input

#endif	// !VOID_ENGINE_INPUT_MOUSE_HPP
