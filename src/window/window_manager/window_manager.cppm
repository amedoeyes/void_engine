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
		std::string_view title, const glm::ivec2& size, const Monitor& monitor, const window& share, const Hints& hints = {}
	) -> window&;

	auto create(std::string_view title, const glm::ivec2& size, const Monitor& monitor, const Hints& hints = {})
		-> window&;

	auto create(std::string_view title, const glm::ivec2& size, const window& share, const Hints& hints = {}) -> window&;

	auto create(std::string_view title, const glm::ivec2& size, const Hints& hints = {}) -> window&;

	auto destroy(const window& window) -> void;

	auto poll_events() -> void;

	auto clear_context() -> void;

	static auto set_swap_interval(std::int32_t interval) -> void;

	static auto set_vsync(bool enabled) -> void;

	[[nodiscard]]
	static auto monitors() -> std::vector<Monitor>;

	[[nodiscard]]
	static auto primary_monitor() -> std::optional<Monitor>;

private:
	static inline std::int32_t instance_count_ = 0;
	std::vector<std::unique_ptr<window>> windows_;
};

} // namespace void_engine::window
