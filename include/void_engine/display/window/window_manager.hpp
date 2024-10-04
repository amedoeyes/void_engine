#ifndef VOID_ENGINE_DISPLAY_WINDOW_WINDOW_MANAGER_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_WINDOW_MANAGER_HPP

#include "void_engine/display/window/hints.hpp"
#include "void_engine/display/window/window.hpp"
#include "void_engine/utility/string_hash.hpp"

#include <functional>
#include <glm/ext/vector_int2.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace void_engine::display::window {

class WindowManager {
public:
	WindowManager(const WindowManager&) = default;
	WindowManager(WindowManager&&) = default;
	auto operator=(const WindowManager&) -> WindowManager& = default;
	auto operator=(WindowManager&&) -> WindowManager& = default;
	WindowManager() = default;
	~WindowManager();

	void update();

	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size,
		const monitor::Monitor& monitor, const Window& share, const Hints& hints = {}
	) -> Window&;
	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size,
		const monitor::Monitor& monitor, const Hints& hints = {}
	) -> Window&;
	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size, const Window& share,
		const Hints& hints = {}
	) -> Window&;
	auto create(
		std::string_view name, std::string_view title, const glm::ivec2& size, const Hints& hints = {}
	) -> Window&;
	void destroy(std::string_view name);
	[[nodiscard]] auto get(std::string_view name) -> Window&;
	[[nodiscard]] auto get_all() -> std::vector<Window*>;

private:
	std::unordered_map<std::string, Window*, utility::string_hash, std::equal_to<>> _windows;

	auto create_window(
		std::string_view title, const glm::ivec2& size, const monitor::Monitor* monitor,
		const Window* share, const Hints& hints
	) -> Window*;
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_WINDOW_MANAGER_HPP
