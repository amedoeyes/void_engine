#ifndef VOID_ENGINE_WINDOW_EVENTS_DROP_EVENT_HPP
#define VOID_ENGINE_WINDOW_EVENTS_DROP_EVENT_HPP

#include <filesystem>
#include <vector>

namespace void_engine::window::events {

struct DropEvent {
	std::vector<std::filesystem::path> paths;
};

} // namespace void_engine::window::events

#endif // !VOID_ENGINE_WINDOW_EVENTS_DROP_EVENT_HPP
