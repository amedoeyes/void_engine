#ifndef VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP
#define VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP

#include "void_engine/window/window.hpp"

#include <glm/ext/vector_float2.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

namespace void_engine::window {

class WindowManager {
public:
	static void init();
	static void terminate();

	static auto create(std::string_view name, std::string_view title, const glm::vec2& size)
		-> Window&;
	static void destroy(std::string_view name);
	static auto get(std::string_view name) -> Window&;

	static void update();

private:
	static std::unordered_map<std::string, Window*> _windows;
};

} // namespace void_engine::window

#endif // !VOID_ENGINE_WINDOW_WINDOW_MANAGER_HPP
