#include "void_engine/display/window/window_manager.hpp"

#include "void_engine/display/window/window.hpp"

#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::display::window {

std::unordered_map<std::string, Window*> WindowManager::_windows;

void WindowManager::terminate() {
	for (const auto& [_, window] : _windows) {
		delete window;
	}
	_windows.clear();
	glfwSetErrorCallback(nullptr);
	glfwTerminate();
}

auto WindowManager::create(std::string_view name, std::string_view title, const glm::vec2& size)
	-> Window& {
	assert(_windows.find(std::string(name)) == _windows.end() && "Window already exists");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#endif
	auto [it, _] = _windows.emplace(name, new Window(title, size));
	return *it->second;
}

void WindowManager::destroy(std::string_view name) {
	const auto it = _windows.find(std::string(name));
	assert(it != _windows.end() && "Window does not exist");
	delete it->second;
	_windows.erase(it);
}

auto WindowManager::get(std::string_view name) -> Window& {
	auto it = _windows.find(std::string(name));
	assert(it != _windows.end() && "Window does not exist");
	return *it->second;
}

void WindowManager::update() {
	glfwPollEvents();
	for (const auto& [_, window] : _windows) {
		window->update();
	}
}

void WindowManager::set_hint_resizable(bool value) {
	glfwWindowHint(GLFW_RESIZABLE, static_cast<int>(value));
}

void WindowManager::set_hint_visible(bool value) {
	glfwWindowHint(GLFW_VISIBLE, static_cast<int>(value));
}

void WindowManager::set_hint_decorated(bool value) {
	glfwWindowHint(GLFW_DECORATED, static_cast<int>(value));
}

void WindowManager::set_hint_focused(bool value) {
	glfwWindowHint(GLFW_FOCUSED, static_cast<int>(value));
}

void WindowManager::set_hint_auto_iconify(bool value) {
	glfwWindowHint(GLFW_AUTO_ICONIFY, static_cast<int>(value));
}

void WindowManager::set_hint_floating(bool value) {
	glfwWindowHint(GLFW_FLOATING, static_cast<int>(value));
}

void WindowManager::set_hint_maximized(bool value) {
	glfwWindowHint(GLFW_MAXIMIZED, static_cast<int>(value));
}

void WindowManager::set_hint_center_cursor(bool value) {
	glfwWindowHint(GLFW_CENTER_CURSOR, static_cast<int>(value));
}

void WindowManager::set_hint_transparent_framebuffer(bool value) {
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, static_cast<int>(value));
}

void WindowManager::set_hint_focus_on_show(bool value) {
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, static_cast<int>(value));
}

void WindowManager::set_hint_scale_to_monitor(bool value) {
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, static_cast<int>(value));
}

void WindowManager::set_hint_scale_framebuffer(bool value) {
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, static_cast<int>(value));
}

void WindowManager::set_hint_mouse_passthrough(bool value) {
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, static_cast<int>(value));
}

void WindowManager::set_hint_position_x(int value) {
	glfwWindowHint(GLFW_POSITION_X, value);
}

void WindowManager::set_hint_position_y(int value) {
	glfwWindowHint(GLFW_POSITION_Y, value);
}

void WindowManager::set_hint_red_bits(int value) {
	glfwWindowHint(GLFW_RED_BITS, value);
}

void WindowManager::set_hint_green_bits(int value) {
	glfwWindowHint(GLFW_GREEN_BITS, value);
}

void WindowManager::set_hint_blue_bits(int value) {
	glfwWindowHint(GLFW_BLUE_BITS, value);
}

void WindowManager::set_hint_alpha_bits(int value) {
	glfwWindowHint(GLFW_ALPHA_BITS, value);
}

void WindowManager::set_hint_depth_bits(int value) {
	glfwWindowHint(GLFW_DEPTH_BITS, value);
}

void WindowManager::set_hint_stencil_bits(int value) {
	glfwWindowHint(GLFW_STENCIL_BITS, value);
}

void WindowManager::set_hint_accum_red_bits(int value) {
	glfwWindowHint(GLFW_ACCUM_RED_BITS, value);
}

void WindowManager::set_hint_accum_green_bits(int value) {
	glfwWindowHint(GLFW_ACCUM_GREEN_BITS, value);
}

void WindowManager::set_hint_accum_blue_bits(int value) {
	glfwWindowHint(GLFW_ACCUM_BLUE_BITS, value);
}

void WindowManager::set_hint_accum_alpha_bits(int value) {
	glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, value);
}

void WindowManager::set_hint_aux_buffers(int value) {
	glfwWindowHint(GLFW_AUX_BUFFERS, value);
}

void WindowManager::set_hint_samples(int value) {
	glfwWindowHint(GLFW_SAMPLES, value);
}

void WindowManager::set_hint_refresh_rate(int value) {
	glfwWindowHint(GLFW_REFRESH_RATE, value);
}

void WindowManager::set_hint_stereo(bool value) {
	glfwWindowHint(GLFW_STEREO, static_cast<int>(value));
}

void WindowManager::set_hint_srgb_capable(bool value) {
	glfwWindowHint(GLFW_SRGB_CAPABLE, static_cast<int>(value));
}

void WindowManager::set_hint_doublebuffer(bool value) {
	glfwWindowHint(GLFW_DOUBLEBUFFER, static_cast<int>(value));
}

} // namespace void_engine::display::window
