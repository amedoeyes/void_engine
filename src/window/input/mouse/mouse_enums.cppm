export module void_engine.window:input.mouse_enums;

import std;

export namespace void_engine::window::input::mouse {

enum class Button : std::uint8_t {
	left = 0,
	right = 1,
	middle = 2,
};

enum class ButtonAction : std::uint8_t {
	release = 0,
	press = 1,
};

enum class Mode : std::uint32_t {
	normal = 0x00034001,
	hidden = 0x00034002,
	disabled = 0x00034003,
};

enum class Shape : std::uint32_t {
	arrow = 0x00036001,
	ibeam = 0x00036002,
	crosshair = 0x00036003,
	hand = 0x00036004,
	ew_resize = 0x00036005,
	ns_resize = 0x00036006,
	nwse_resize = 0x00036007,
	nesw_resize = 0x00036008,
	all_resize = 0x00036009,
	not_allowed = 0x0003600A,
};

} // namespace void_engine::window::input::mouse
