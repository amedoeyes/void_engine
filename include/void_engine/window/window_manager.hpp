#ifndef VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP
#define VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP

#include "void_engine/window/window.hpp"

#include <vector>

namespace void_engine::window {

class WindowManager {
public:
	static void init();
	static void terminate();

	static auto create(const char* title, int width, int height) -> Window*;
	static void destroy(Window* window);

	static void poll_events();

private:
	static std::vector<Window*> _windows;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP
