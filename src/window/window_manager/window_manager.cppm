export module void_engine.window:window_manager;

import :window;
import :monitor;
import :window_hints;

import std;
import glm;
import void_engine.utility.string_hash;

export namespace void_engine::window {

class window_manager {
public:
	window_manager(const window_manager&) = default;
	window_manager(window_manager&&) = default;
	auto operator=(const window_manager&) -> window_manager& = default;
	auto operator=(window_manager&&) -> window_manager& = default;
	window_manager();
	~window_manager();

	auto create(
		std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Window& share, const Hints& hints = {}
	) -> Window&;

	auto create(std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints = {})
		-> Window&;

	auto create(std::string_view title, const glm::ivec2& size, const Window& share, const Hints& hints = {}) -> Window&;

	auto create(std::string_view title, const glm::ivec2& size, const Hints& hints = {}) -> Window&;

	auto destroy(const Window& window) -> void;

	auto poll_events() -> void;

	[[nodiscard]]
	static auto monitors() -> std::vector<Monitor>;

	[[nodiscard]]
	static auto primary_monitor() -> std::optional<Monitor>;

private:
	static inline std::int32_t instance_count_ = 0;
	std::vector<std::unique_ptr<Window>> windows_;
};

} // namespace void_engine::window
