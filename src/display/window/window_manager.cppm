export module void_engine.display:window.window_manager;

import :window.window;
import :window.window_hints;

import std;
import glm;
import void_engine.utility.string_hash;

export namespace void_engine::display::window {

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
};

} // namespace void_engine::display::window
