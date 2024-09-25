#ifndef VOID_ENGINE_DISPLAY_WINDOW_ENUMS_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_ENUMS_HPP

#include <cstdint>

namespace void_engine::display::window {

enum class ContextClientAPI : uint32_t {
	none = 0,
	opengl = 0x00030001,
	opengl_es = 0x00030002,
};

enum class ContextCreationAPI : uint32_t {
	native = 0x00036001,
	egl = 0x00036002,
	osmesa = 0x00036003,
};

enum class ContextRobustness : uint32_t {
	none = 0,
	no_reset_notification = 0x00031001,
	lose_context_on_reset = 0x00031002,
};

enum class ContextReleaseBehavior : uint32_t {
	any = 0,
	flush = 0x00035001,
	none = 0x00035002,
};

enum class ContextOpenGLProfile : uint32_t {
	any = 0,
	compatibility = 0x00032002,
	core = 0x00032001,
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_ENUMS_HPP
