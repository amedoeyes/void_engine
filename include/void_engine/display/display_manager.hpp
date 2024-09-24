#ifndef VOID_ENGINE_DISPLAY_DISPLAY_MANAGER_HPP
#define VOID_ENGINE_DISPLAY_DISPLAY_MANAGER_HPP

#include "void_engine/display/monitor/monitor_manager.hpp"
#include "void_engine/display/window/window_manager.hpp"

#include <glm/ext/vector_int2.hpp>

namespace void_engine::display {

class DisplayManager {
public:
	DisplayManager(const DisplayManager&) = default;
	DisplayManager(DisplayManager&&) = default;
	auto operator=(const DisplayManager&) -> DisplayManager& = default;
	auto operator=(DisplayManager&&) -> DisplayManager& = default;
	DisplayManager();
	~DisplayManager();

	auto windows() -> window::WindowManager&;
	auto monitors() -> monitor::MonitorManager&;

private:
	static inline unsigned int _instance_count;
	window::WindowManager* _window_manager;
	monitor::MonitorManager* _monitor_manager;
};

} // namespace void_engine::display

#endif // ! VOID_ENGINE_DISPLAY_DISPLAY_MANAGER_HPP
