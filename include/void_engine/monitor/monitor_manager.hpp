#ifndef VOID_ENGINE_MONITOR_MONITOR_MANAGER_HPP
#define VOID_ENGINE_MONITOR_MONITOR_MANAGER_HPP

#include "void_engine/monitor/monitor.hpp"

#include <vector>

namespace void_engine::monitor {

class MonitorManager {
public:
	static void init();
	static void terminate();

	static auto get_monitors() -> const std::vector<Monitor*>&;
	static auto get_primary_monitor() -> Monitor&;

private:
	static std::vector<Monitor*> _monitor;
};

} // namespace void_engine::monitor

#endif // !VOID_ENGINE_MONITOR_MONITOR_MANAGER_HPP
