#ifndef VOID_ENGINE_MONITOR_MONITOR_MANAGER_HPP
#define VOID_ENGINE_MONITOR_MONITOR_MANAGER_HPP

#include "void_engine/monitor/monitor.hpp"

#include <string_view>
#include <vector>

namespace void_engine::monitor {

class MonitorManager {
public:
	static auto get(std::string_view name) -> Monitor&;
	static auto get_all() -> const std::vector<Monitor*>&;
	static auto get_primary() -> Monitor&;

private:
	static std::vector<Monitor*> _monitor;

	static void init();
	static void terminate();
};

} // namespace void_engine::monitor

#endif // !VOID_ENGINE_MONITOR_MONITOR_MANAGER_HPP
