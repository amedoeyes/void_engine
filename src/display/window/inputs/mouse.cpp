#include "void_engine/display/window/inputs/mouse.hpp"

#include "void_engine/resources/image.hpp"
#include "void_engine/utils/get_exec_path.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>

namespace void_engine::display::window::inputs {

Mouse::Mouse(GLFWwindow& window) : _window(&window) {
}

Mouse::~Mouse() {
	if (_cursor != nullptr) {
		glfwDestroyCursor(_cursor);
	}
}

void Mouse::set_mode(MouseMode mode) const {
	glfwSetInputMode(_window, GLFW_CURSOR, static_cast<int>(mode));
}

void Mouse::set_raw_motion(bool value) const {
	glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, static_cast<int>(value));
}

void Mouse::set_shape(MouseShape shape) {
	if (_cursor != nullptr) {
		glfwDestroyCursor(_cursor);
	}
	_cursor = glfwCreateStandardCursor(static_cast<int>(shape));
	assert(_cursor != nullptr && "Failed to create cursor");
	glfwSetCursor(_window, _cursor);
}

void Mouse::set_image(const std::filesystem::path& path, const glm::vec2& hot_spot) {
	if (_cursor != nullptr) {
		glfwDestroyCursor(_cursor);
	}
	resources::Image* image = resources::read_image(utils::get_exec_path().parent_path() / path);
	assert(image != nullptr && "Failed to read image");
	const GLFWimage glfw_image = {
		static_cast<int>(image->width),
		static_cast<int>(image->height),
		image->bytes.data(),
	};
	_cursor =
		glfwCreateCursor(&glfw_image, static_cast<int>(hot_spot.x), static_cast<int>(hot_spot.y));
	assert(_cursor != nullptr && "Failed to create cursor");
	glfwSetCursor(_window, _cursor);
}

auto Mouse::is_down(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return it->second.current;
}

auto Mouse::is_up(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return !it->second.current;
}

auto Mouse::is_pressed(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return it->second.current && !it->second.previous;
}

auto Mouse::get_position() const -> glm::vec2 {
	return _position.current;
}

auto Mouse::get_delta_position() const -> glm::vec2 {
	return _position.current - _position.previous;
}

auto Mouse::get_scroll() const -> glm::vec2 {
	return _scroll;
}

void Mouse::update() {
	for (auto& [_, button] : _buttons) {
		button.previous = button.current;
	}
	_position.previous = _position.current;
}

void Mouse::set_button(MouseButton button, bool state) {
	_buttons[button].current = state;
}

void Mouse::set_position(const glm::vec2& position) {
	_position.current = position;
}

void Mouse::set_scroll(const glm::vec2& scroll) {
	_scroll = scroll;
}

} // namespace void_engine::display::window::inputs
