#ifndef VOID_ENGINE_DISPLAY_WINDOW_HINTS_HPP
#define VOID_ENGINE_DISPLAY_WINDOW_HINTS_HPP

#include "void_engine/display/window/enums.hpp"

#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_int4.hpp>
#include <limits>
#include <string>
#include <utility>
namespace void_engine::display::window {

struct WindowHints {
	// Whether the window will be resizable by the user.
	bool resizable = true;
	// Whether the window will be initially visible.
	bool visible = true;
	// Whether the window will have window decorations such as a border, a close widget, etc.
	bool decorated = true;
	// Whether the window will be given input focus when created.
	bool focused = true;
	// Weather the full screen window will automatically minimize and restore the previous video mode
	// on input focus loss.
	bool auto_minimize = true;
	// Whether the window will be always on top of other regular windows.
	bool floating = false;
	// Whether the windowed mode window will be maximized when created.
	bool maximized = false;
	// Whether the cursor should be centered over newly created full screen windows.
	bool center_cursor = true;
	// Whether window framebuffer will be transparent.
	bool transparent_framebuffer = false;
	// Whether the window will be given input focus when shown.
	bool focus_on_show = true;
	// Whether the window content area should be resized based on monitor content scale changes.
	bool scale_to_monitor = false;
	// Whether the framebuffer should be resized based on monitor content scale changes.
	bool scale_framebuffer = true;
	// Whether the window is transparent to mouse input.
	bool mouse_passthrough = false;
	// The initial position of the window.
	glm::ivec2 position = {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
};

struct FramebufferHints {
	// The desired bit depth of color components in the default framebuffer.
	glm::ivec4 color_bits = {8, 8, 8, 8};
	// The desired bit depth of the default framebuffer's depth buffer.
	int depth_bits = 24;
	// The desired bit depth of the default framebuffer's stencil buffer.
	int stencil_bits = 8;
	// The desired bit depth of color components in the accumulation buffer.
	glm::ivec4 accumulation_color_bits = {0, 0, 0, 0};
	// The desired number of auxiliary buffers.
	int auxiliary_buffers = 0;
	// Weather to use stereoscopic rendering.
	bool stereo = false;
	// The desired number of samples to use for multisampling.
	int samples = 0;
	// Weather the framebuffer should be sRGB capable.
	bool srgb_capable = false;
	// Weather the framebuffer should be double buffered.
	bool doublebuffer = true;
};

struct MonitorHints {
	// The desired refresh rate for full screen windows.
	int refresh_rate = -1;
};

struct ContextHints {
	// Which client API to create the context for.
	ContextClientAPI client_api = ContextClientAPI::opengl;
	// Which context creation API to use to create the context.
	ContextCreationAPI creation_api = ContextCreationAPI::native;
	// The client API version that the created context must be compatible with.
	std::pair<int, int> version = {4, 6};
	// Whether the OpenGL context should be forward-compatible.
	bool opengl_forward_compat = false;
	// Whether the context should be created in debug mode.
	bool debug = false;
	// Which OpenGL profile to create the context for.
	ContextOpenGLProfile opengl_profile = ContextOpenGLProfile::core;
	// The robustness strategy to be used by the context.
	ContextRobustness robustness = ContextRobustness::none;
	// The release behavior to be used by the context.
	ContextReleaseBehavior release_behavior = ContextReleaseBehavior::any;
	// Whether errors should be generated by the context.
	bool no_error = false;
};

struct Win32Hints {
	// Whether to allow access to the window menu via the Alt+Space and Alt-and-then-Space keyboard
	// shortcuts.
	bool keyboard_menu = false;
	// Whether to show the window the way specified in the program's STARTUPINFO when it is shown for
	// the first time.
	bool showdefault = false;
};

struct CocoaHints {
	// The UTF-8 encoded name to use for autosaving the window frame, or if empty disables frame
	// autosaving for the window.
	std::string frame_name;
	// Whether to enable automatic graphics switching to the most appropriate GPU on multi-GPU
	// systems.
	bool graphics_switching = false;
};

struct WaylandHints {
	// The Wayland app_id for a window, used by window managers to identify types of windows.
	std::string app_id;
};

struct X11Hints {
	// The desired ASCII encoded class part of the ICCCM WM_CLASS window property.
	std::string class_name;
	// The desired ASCII encoded instance part of the ICCCM WM_CLASS window property.
	std::string instance_name;
};

struct Hints {
	WindowHints window = {};
	FramebufferHints framebuffer = {};
	MonitorHints monitor = {};
	ContextHints context = {};
	Win32Hints win32 = {};
	CocoaHints cocoa = {};
	WaylandHints wayland = {};
	X11Hints x11 = {};
};

} // namespace void_engine::display::window

#endif // !VOID_ENGINE_DISPLAY_WINDOW_HINTS_HPP
