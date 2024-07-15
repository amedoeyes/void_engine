#ifndef VOID_ENGINE_DISPLAY_MONITOR_MONITOR_MANAGER_HPP
#define VOID_ENGINE_DISPLAY_MONITOR_MONITOR_MANAGER_HPP

#include "void_engine/display/monitor/monitor.hpp"

#include <string_view>
#include <vector>

namespace void_engine::display {

class DisplayManager;

namespace monitor {

class MonitorManager {
	friend class display::DisplayManager;

public:
	static auto get(std::string_view name) -> Monitor&;
	static auto get_all() -> const std::vector<Monitor*>&;
	static auto get_primary() -> Monitor&;

private:
	static std::vector<Monitor*> _monitors;

	static void init();
	static void terminate();
};

} // namespace monitor

} // namespace void_engine::display

#endif // !VOID_ENGINE_DISPLAY_MONITOR_MONITOR_MANAGER_HPP
