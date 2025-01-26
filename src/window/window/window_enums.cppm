export module void_engine.window:window_enums;

import std;

export namespace void_engine::window {

enum class ContextClientAPI : std::uint32_t {
	none = 0,
	opengl = 0x00030001,
	opengl_es = 0x00030002,
};

enum class ContextCreationAPI : std::uint32_t {
	native = 0x00036001,
	egl = 0x00036002,
	osmesa = 0x00036003,
};

enum class ContextRobustness : std::uint32_t {
	none = 0,
	no_reset_notification = 0x00031001,
	lose_context_on_reset = 0x00031002,
};

enum class ContextReleaseBehavior : std::uint32_t {
	any = 0,
	flush = 0x00035001,
	none = 0x00035002,
};

enum class ContextOpenGLProfile : std::uint32_t {
	any = 0,
	compatibility = 0x00032002,
	core = 0x00032001,
};

} // namespace void_engine::window
