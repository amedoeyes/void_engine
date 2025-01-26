export module void_engine.window:window_manager;

import :window;
import :monitor;
import :window_hints;

import std;
import glm;
import void_engine.utility.string_hash;

export namespace void_engine::window {

class WindowManager {
public:
	WindowManager(const WindowManager&) = default;
	WindowManager(WindowManager&&) = default;
	auto operator=(const WindowManager&) -> WindowManager& = default;
	auto operator=(WindowManager&&) -> WindowManager& = default;
	WindowManager();
	~WindowManager();

	auto create(
		std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Window& share,
		const Hints& hints = {}
	) -> Window&;
	auto create(
		std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints = {}
	) -> Window&;
	auto create(
		std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints = {}
	) -> Window&;
	auto create(std::string_view title, const glm::ivec2& size, const Hints& hints = {}) -> Window&;
	void destroy(const Window& window);

	void poll_events();

	[[nodiscard]] auto get_windows() -> std::span<Window>;
	[[nodiscard]] static auto get_monitor(std::string_view name) -> Monitor&;
	[[nodiscard]] static auto get_monitors() -> std::span<Monitor>;
	[[nodiscard]] static auto get_primary_monitor() -> Monitor&;

private:
	static inline std::int32_t _instance_count;
	std::vector<Window> _windows;
	static inline std::vector<Monitor> _monitors;
};

} // namespace void_engine::window
