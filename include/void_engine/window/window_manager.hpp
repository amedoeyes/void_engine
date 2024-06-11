#ifndef VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP
#define VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP

#include "void_engine/window/window.hpp"

#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::window {

class WindowManager {
public:
	static void init();
	static void terminate();

	static auto create(
		const std::string& name, const std::string_view title, int width,
		int height
	) -> Window*;
	static void destroy(const std::string& name);
	static auto get(const std::string& name) -> Window*;

	static void poll_events();

private:
	static std::unordered_map<std::string, Window*> _windows;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP
