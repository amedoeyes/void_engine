#ifndef VOID_ENGINE_DISPLAY_WINDOW_INPUT_MOUSE_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_INPUT_MOUSE_HPP

#include "void_engine/display/window/input/input_state.hpp"

#include <cstdint>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>
#include <unordered_map>

struct GLFWwindow;
struct GLFWcursor;

namespace void_engine::display::window {

class WindowInputHandler;
class Window;

namespace input {

enum class MouseButton : std::uint8_t {
	left = 0,
	right = 1,
	middle = 2,
};

enum class MouseMode {
	normal = 0x00034001,
	hidden = 0x00034002,
	disabled = 0x00034003,
};

enum class MouseShape {
	arrow = 0x00036001,
	ibeam = 0x00036002,
	crosshair = 0x00036003,
	hand = 0x00036004,
	ew_resize = 0x00036005,
	ns_resize = 0x00036006,
	nwse_resize = 0x00036007,
	nesw_resize = 0x00036008,
	all_resize = 0x00036009,
	not_allowed = 0x0003600A,
};

class Mouse {
	friend class window::WindowInputHandler;

public:
	Mouse(const Mouse&) = default;
	Mouse(Mouse&&) = delete;
	auto operator=(const Mouse&) -> Mouse& = default;
	auto operator=(Mouse&&) -> Mouse& = delete;
	explicit Mouse(GLFWwindow& window);
	~Mouse();

	void set_mode(MouseMode mode) const;
	void set_raw_motion(bool value) const;
	void set_shape(MouseShape shape);
	void set_image(const std::filesystem::path& path, const glm::vec2& hot_spot = glm::vec2(0.f));

	[[nodiscard]] auto is_down(MouseButton button) const -> bool;
	[[nodiscard]] auto is_up(MouseButton button) const -> bool;
	[[nodiscard]] auto is_pressed(MouseButton button) const -> bool;
	[[nodiscard]] auto get_position() const -> glm::vec2;
	[[nodiscard]] auto get_delta_position() const -> glm::vec2;
	[[nodiscard]] auto get_scroll() const -> glm::vec2;

private:
	GLFWwindow* _window;
	GLFWcursor* _cursor = nullptr;
	std::unordered_map<MouseButton, InputState<bool>> _buttons;
	InputState<glm::vec2> _position;
	glm::vec2 _scroll = glm::vec2(0.f);

	void update();
	void set_button(MouseButton button, bool state);
	void set_position(const glm::vec2& position);
	void set_scroll(const glm::vec2& scroll);
};

} // namespace input

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_INPUT_MOUSE_HPP
