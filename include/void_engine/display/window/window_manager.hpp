#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_MANAGER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_MANAGER_HPP

#include "void_engine/display/window/window.hpp"

#include <glm/ext/vector_int2.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::display::window {

class WindowManager {
public:
	WindowManager(const WindowManager&) = default;
	WindowManager(WindowManager&&) = default;
	auto operator=(const WindowManager&) -> WindowManager& = default;
	auto operator=(WindowManager&&) -> WindowManager& = default;
	WindowManager();
	~WindowManager();

	void update();

	auto create(std::string_view name, std::string_view title, const glm::ivec2& size) -> Window&;
	void destroy(std::string_view name);
	[[nodiscard]] auto get(std::string_view name) -> Window&;
	[[nodiscard]] auto get_all() -> std::vector<Window*>;

	static void set_hint_resizable(bool value);
	static void set_hint_visible(bool value);
	static void set_hint_decorated(bool value);
	static void set_hint_focused(bool value);
	static void set_hint_auto_iconify(bool value);
	static void set_hint_floating(bool value);
	static void set_hint_maximized(bool value);
	static void set_hint_center_cursor(bool value);
	static void set_hint_transparent_framebuffer(bool value);
	static void set_hint_focus_on_show(bool value);
	static void set_hint_scale_to_monitor(bool value);
	static void set_hint_scale_framebuffer(bool value);
	static void set_hint_mouse_passthrough(bool value);
	static void set_hint_position_x(int value);
	static void set_hint_position_y(int value);
	static void set_hint_red_bits(int value);
	static void set_hint_green_bits(int value);
	static void set_hint_blue_bits(int value);
	static void set_hint_alpha_bits(int value);
	static void set_hint_depth_bits(int value);
	static void set_hint_stencil_bits(int value);
	static void set_hint_accum_red_bits(int value);
	static void set_hint_accum_green_bits(int value);
	static void set_hint_accum_blue_bits(int value);
	static void set_hint_accum_alpha_bits(int value);
	static void set_hint_aux_buffers(int value);
	static void set_hint_samples(int value);
	static void set_hint_refresh_rate(int value);
	static void set_hint_stereo(bool value);
	static void set_hint_srgb_capable(bool value);
	static void set_hint_doublebuffer(bool value);

private:
	std::unordered_map<std::string, Window*> _windows;
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_MANAGER_HPP
