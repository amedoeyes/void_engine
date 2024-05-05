#ifndef VOID_ENGINE_INPUT_MOUSE_HPP
#define VOID_ENGINE_INPUT_MOUSE_HPP

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace void_engine::input {

class Mouse {
	public:
	enum class Button {
		left = 0,
		right = 1,
		middle = 2
	};
	struct Position {
		float x;
		float y;
	};
	struct Scroll {
		float x;
		float y;
	};

	public:
	void update();

	bool is_button_down(Button button) const;
	bool is_button_up(Button button) const;
	bool is_button_pressed(Button button) const;

	Position get_position() const;
	void set_position(float x, float y);

	Scroll get_scroll() const;
	void set_scroll(float x, float y);

	bool get_state(Button button) const;
	void set_state(Button button, bool state);

	bool get_prev_state(Button button) const;
	void set_prev_state(Button button, bool state);

	static void button_callback(
		GLFWwindow* window, int button, int action, [[maybe_unused]] int mods
	);
	static void position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(
		GLFWwindow* window, double xoffset, double yoffset
	);

	private:
	std::unordered_map<Button, bool> _states;
	std::unordered_map<Button, bool> _prev_states;
	Position _position = {0.0f, 0.0f};
	Scroll _scroll = {0.0f, 0.0f};
};

}  // namespace void_engine::input

#endif	// !VOID_ENGINE_INPUT_MOUSE_HPP
