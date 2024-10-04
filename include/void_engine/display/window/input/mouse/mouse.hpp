#ifndef VOID_ENGINE_DISPLAY_WINDOW_INPUT_MOUSE_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_INPUT_MOUSE_HPP

#include "void_engine/display/window/input/mouse/enums.hpp"
#include "void_engine/utility/event.hpp"
#include "void_engine/utility/state.hpp"

#include <array>
#include <filesystem>
#include <glm/ext/vector_float2.hpp>

struct GLFWwindow;
struct GLFWcursor;

namespace void_engine::display::window {

class Window;

namespace input::mouse {

class Mouse {
public:
	Mouse(const Mouse&) = default;
	Mouse(Mouse&&) = delete;
	auto operator=(const Mouse&) -> Mouse& = default;
	auto operator=(Mouse&&) -> Mouse& = delete;
	explicit Mouse(Window& window);
	~Mouse();

	void update();

	void set_button(Button button, bool state);
	void set_position(const glm::vec2& position);
	void set_scroll(const glm::vec2& scroll);
	void set_mode(Mode mode) const;
	void set_raw_motion(bool enabled) const;
	void set_shape(Shape shape);
	void set_image(const std::filesystem::path& path, const glm::vec2& hot_spot = {0.0f, 0.0f});

	[[nodiscard]] auto get_position() const -> glm::vec2;
	[[nodiscard]] auto get_delta_position() const -> glm::vec2;
	[[nodiscard]] auto get_scroll() const -> glm::vec2;

	[[nodiscard]] auto is_down(Button button) const -> bool;
	[[nodiscard]] auto is_up(Button button) const -> bool;
	[[nodiscard]] auto is_pressed(Button button) const -> bool;
	[[nodiscard]] auto is_released(Button button) const -> bool;

private:
	Window* _window;
	GLFWcursor* _cursor = nullptr;
	std::array<utility::State<bool>, 4> _buttons;
	utility::State<glm::vec2> _position;
	glm::vec2 _scroll = {0.0f, 0.0f};
	utility::event::EventListenerID _mouse_button_listener;
	utility::event::EventListenerID _mouse_position_listener;
	utility::event::EventListenerID _mouse_scroll_listener;
};

} // namespace input::mouse

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_INPUT_MOUSE_HPP
