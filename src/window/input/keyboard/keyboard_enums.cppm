export module void_engine.window:input.keyboard_enums;

import std;

export namespace void_engine::window::input::keyboard {

enum class Key : std::uint16_t {
	none = 0,
	space = 32,
	apostrophe = 39,
	comma = 44,
	minus = 45,
	period = 46,
	slash = 47,
	num_0 = 48,
	num_1 = 49,
	num_2 = 50,
	num_3 = 51,
	num_4 = 52,
	num_5 = 53,
	num_6 = 54,
	num_7 = 55,
	num_8 = 56,
	num_9 = 57,
	semicolon = 59,
	equal = 61,
	a = 65,
	b = 66,
	c = 67,
	d = 68,
	e = 69,
	f = 70,
	g = 71,
	h = 72,
	i = 73,
	j = 74,
	k = 75,
	l = 76,
	m = 77,
	n = 78,
	o = 79,
	p = 80,
	q = 81,
	r = 82,
	s = 83,
	t = 84,
	u = 85,
	v = 86,
	w = 87,
	x = 88,
	y = 89,
	z = 90,
	left_bracket = 91,
	backslash = 92,
	right_bracket = 93,
	backtick = 96,
	escape = 256,
	enter = 257,
	tab = 258,
	backspace = 259,
	insert = 260,
	del = 261,
	right = 262,
	left = 263,
	down = 264,
	up = 265,
	page_up = 266,
	page_down = 267,
	home = 268,
	end = 269,
	caps_lock = 280,
	scroll_lock = 281,
	num_lock = 282,
	print_screen = 283,
	pause = 284,
	f1 = 290,
	f2 = 291,
	f3 = 292,
	f4 = 293,
	f5 = 294,
	f6 = 295,
	f7 = 296,
	f8 = 297,
	f9 = 298,
	f10 = 299,
	f11 = 300,
	f12 = 301,
	left_shift = 340,
	left_control = 341,
	left_alt = 342,
	left_super = 343,
	right_shift = 344,
	right_control = 345,
	right_alt = 346,
	right_super = 347,
	menu = 348
};

enum class KeyAction : std::uint8_t {
	release = 0,
	press = 1,
	repeat = 2,
};

enum class KeyMod : std::uint8_t {
	shift = 0x0001,
	control = 0x0002,
	alt = 0x0004,
	super = 0x0008,
	caps_lock = 0x0010,
	num_lock = 0x0020,
};

} // namespace void_engine::window::input::keyboard
