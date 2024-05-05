#ifndef VOID_WINDOW_MANAGER_HPP
#define VOID_WINDOW_MANAGER_HPP

#include <vector>

#include "void_engine/window/window.hpp"

namespace void_engine::window {

class WindowManager {
	public:
	static void init();
	static void terminate();

	static Window* create(
		const char* title, const int& width, const int& height
	);
	static void destroy(Window* window);

	private:
	static std::vector<Window*> _windows;
};

}  // namespace void_engine::window

#endif	// !VOID_WINDOW_MANAGER_HPP
