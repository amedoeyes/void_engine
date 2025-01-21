#ifndef VOID_ENGINE_DISPLAY_MONITOR_MONITOR_MANAGER_HPP
#define VOID_ENGINE_DISPLAY_MONITOR_MONITOR_MANAGER_HPP

#include <span>
#include <string_view>
#include <vector>

namespace void_engine::display::monitor {
class Monitor;

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

#endif // !VOID_ENGINE_DISPLAY_MONITOR_MONITOR_MANAGER_HPP
