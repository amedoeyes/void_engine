module;

#include "void_engine/resource/image/image.hpp"

#include <GLFW/glfw3.h>

module void_engine.display.window;
import :input.mouse;

import std;
import glm;

namespace void_engine::display::window::input::mouse {

Mouse::Mouse(Window& window) : _window(&window) {
	WindowEventHandler& events = _window->get_event_handler();
	_mouse_button_listener =
		events.add_listener<event::MouseButtonEvent>([this](const event::MouseButtonEvent& event) {
			set_button(event.button, event.action == input::mouse::ButtonAction::press);
		});
	_mouse_position_listener =
		events.add_listener<event::MousePositionEvent>([this](const event::MousePositionEvent& event) {
			set_position(event.position);
		});
	_mouse_scroll_listener =
		events.add_listener<event::MouseScrollEvent>([this](const event::MouseScrollEvent& event) {
			set_scroll(event.offset);
		});
}

Mouse::~Mouse() {
	WindowEventHandler& events = _window->get_event_handler();
	events.remove_listener<event::MouseButtonEvent>(_mouse_button_listener);
	events.remove_listener<event::MousePositionEvent>(_mouse_position_listener);
	events.remove_listener<event::MouseScrollEvent>(_mouse_scroll_listener);
	if (_cursor != nullptr) {
		glfwDestroyCursor(_cursor);
	}
}

void Mouse::update() {
	for (auto& button : _buttons) {
		button.set_previous(button.get());
	}
	_position.set_previous(_position.get());
}

void Mouse::set_button(Button button, bool state) {
	_buttons[static_cast<size_t>(button)].set_current(state);
}

void Mouse::set_position(const glm::vec2& position) {
	_position.set_current(position);
}

void Mouse::set_scroll(const glm::vec2& scroll) {
	_scroll = scroll;
}

void Mouse::set_mode(Mode mode) const {
	glfwSetInputMode(_window->raw(), GLFW_CURSOR, static_cast<int>(mode));
}

void Mouse::set_raw_motion(bool enabled) const {
	glfwSetInputMode(_window->raw(), GLFW_RAW_MOUSE_MOTION, static_cast<int>(enabled));
}

void Mouse::set_shape(Shape shape) {
	if (_cursor != nullptr) {
		glfwDestroyCursor(_cursor);
	}
	_cursor = glfwCreateStandardCursor(static_cast<int>(shape));
	assert(_cursor != nullptr && "Failed to create cursor");
	glfwSetCursor(_window->raw(), _cursor);
}

void Mouse::set_image(const std::filesystem::path& path, const glm::vec2& hot_spot) {
	if (_cursor != nullptr) {
		glfwDestroyCursor(_cursor);
	}
	const resource::image::Image image(path, true);
	const glm::ivec2& size = image.get_size();
	const GLFWimage glfw_image = {
		.width = size.x,
		.height = size.y,
		.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
	};
	_cursor =
		glfwCreateCursor(&glfw_image, static_cast<int>(hot_spot.x), static_cast<int>(hot_spot.y));
	assert(_cursor != nullptr && "Failed to create cursor");
	glfwSetCursor(_window->raw(), _cursor);
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

auto Mouse::is_down(Button button) const -> bool {
	return _buttons[static_cast<size_t>(button)].get();
}

auto Mouse::is_up(Button button) const -> bool {
	return !_buttons[static_cast<size_t>(button)].get();
}

auto Mouse::is_pressed(Button button) const -> bool {
	return _buttons[static_cast<size_t>(button)].entered(true);
}

auto Mouse::is_released(Button button) const -> bool {
	return _buttons[static_cast<size_t>(button)].exited(true);
}

} // namespace void_engine::display::window::input::mouse
