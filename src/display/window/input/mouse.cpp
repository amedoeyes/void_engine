#include "void_engine/display/window/input/mouse.hpp"

#include "void_engine/resource/image/image.hpp"
#include "void_engine/utility/get_exec_path.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>

namespace void_engine::display::window::input {

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
	const resource::image::Image image(utility::get_exec_path().parent_path() / path, true);
	const glm::uvec2 size = image.get_size();
	const GLFWimage glfw_image = {
		.width = static_cast<int>(size.x),
		.height = static_cast<int>(size.y),
		.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
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
	return it->second.get();
}

auto Mouse::is_up(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return !it->second.get();
}

auto Mouse::is_pressed(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return it->second.entered(true);
}

auto Mouse::is_released(MouseButton button) const -> bool {
	const auto it = _buttons.find(button);
	if (it == _buttons.end()) {
		return false;
	}
	return it->second.exited(true);
}

auto Mouse::get_position() const -> glm::vec2 {
	return _position.get();
}

auto Mouse::get_delta_position() const -> glm::vec2 {
	return _position.get() - _position.get_previous();
}

auto Mouse::get_scroll() const -> glm::vec2 {
	return _scroll;
}

void Mouse::update() {
	for (auto& [_, button] : _buttons) {
		button.set_previous(button.get());
	}
	_position.set_previous(_position.get());
}

void Mouse::set_button(MouseButton button, bool state) {
	_buttons[button].set_current(state);
}

void Mouse::set_position(const glm::vec2& position) {
	_position.set_current(position);
}

void Mouse::set_scroll(const glm::vec2& scroll) {
	_scroll = scroll;
}

} // namespace void_engine::display::window::input
