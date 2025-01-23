export module void_engine.display:monitor.monitor_manager;

import :monitor.monitor;

import std;

export namespace void_engine::display::monitor {

class MonitorManager {
public:
	MonitorManager(const MonitorManager&) = default;
	MonitorManager(MonitorManager&&) = default;
	auto operator=(const MonitorManager&) -> MonitorManager& = default;
	auto operator=(MonitorManager&&) -> MonitorManager& = default;
	MonitorManager();
	~MonitorManager();

	[[nodiscard]] static auto get(std::string_view name) -> Monitor&;
	[[nodiscard]] static auto get_all() -> std::span<Monitor*>;
	[[nodiscard]] static auto get_primary() -> Monitor&;

private:
	static inline unsigned int _instance_count;
	static inline std::vector<Monitor*> _monitors;
};

} // namespace void_engine::display::monitor
