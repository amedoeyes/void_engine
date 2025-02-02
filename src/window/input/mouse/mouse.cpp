module;

#include <cassert>
#include <GLFW/glfw3.h>

module void_engine.window;

import std;
import glm;
import void_engine.resources;

namespace void_engine::window::input {

mouse::mouse(window& window) : window_{window} {
	button_listener_id_ = window_.get().events().add_listener<event::mouse_button>([&](const auto& event) {
		set_button(event.button, event.action == mouse_action::press);
	});
	position_listener_id_ = window_.get().events().add_listener<event::mouse_position>([&](const auto& event) {
		set_position(event.position);
	});
	scroll_listener_id_ = window_.get().events().add_listener<event::mouse_scroll>([&](const auto& event) {
		set_scroll(event.offset);
	});
}

mouse::~mouse() {
	window_.get().events().remove_listener<event::mouse_button>(button_listener_id_);
	window_.get().events().remove_listener<event::mouse_position>(position_listener_id_);
	window_.get().events().remove_listener<event::mouse_scroll>(scroll_listener_id_);
}

auto mouse::update() -> void {
	for (auto& button : buttons_) button.set_previous(button.get());
	position_.set_previous(position_.get());
}

auto mouse::set_button(mouse_button button, bool state) -> void {
	buttons_.at(std::to_underlying(button)).set_current(state);
}

auto mouse::set_position(const glm::vec2& position) -> void {
	position_.set_current(position);
}

auto mouse::set_scroll(const glm::vec2& scroll) -> void {
	scroll_ = scroll;
}

auto mouse::set_mode(mouse_mode mode) const -> void {
	glfwSetInputMode(window_.get().raw(), GLFW_CURSOR, std::to_underlying(mode));
}

auto mouse::set_raw_motion(bool enabled) const -> void {
	glfwSetInputMode(window_.get().raw(), GLFW_RAW_MOUSE_MOTION, static_cast<int>(enabled));
}

auto mouse::set_shape(mouse_shape shape) -> void {
	cursor_.reset(glfwCreateStandardCursor(std::to_underlying(shape)));
	assert(cursor_ != nullptr && "Failed to create cursor");
	glfwSetCursor(window_.get().raw(), cursor_.get());
}

auto mouse::set_image(const resources::Image& image, const glm::ivec2& hot_spot) -> void {
	const auto glfw_image = GLFWimage{
		.width = image.get_size().x,
		.height = image.get_size().y,
		.pixels = std::bit_cast<unsigned char*>(image.get_data().data()),
	};
	cursor_.reset(glfwCreateCursor(&glfw_image, hot_spot.x, hot_spot.y));
	assert(cursor_ != nullptr && "Failed to create cursor");
	glfwSetCursor(window_.get().raw(), cursor_.get());
}

auto mouse::position() const -> glm::vec2 {
	return position_.get();
}

auto mouse::delta_position() const -> glm::vec2 {
	return position_.get() - position_.get_previous();
}

auto mouse::scroll() const -> glm::vec2 {
	return scroll_;
}

auto mouse::is_down(mouse_button button) const -> bool {
	return buttons_.at(std::to_underlying(button)).get();
}

auto mouse::is_up(mouse_button button) const -> bool {
	return !buttons_.at(std::to_underlying(button)).get();
}

auto mouse::is_pressed(mouse_button button) const -> bool {
	return buttons_.at(std::to_underlying(button)).entered(true);
}

auto mouse::is_released(mouse_button button) const -> bool {
	return buttons_.at(std::to_underlying(button)).exited(true);
}

} // namespace void_engine::window::input
