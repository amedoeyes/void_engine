#ifndef VOID_ENGINE_RESOURCE_TEXTURE_ENUMS_HPP
#define VOID_ENGINE_RESOURCE_TEXTURE_ENUMS_HPP

#include <cstdint>
namespace void_engine::resource {

enum class Target : uint16_t {
	texture_1d = 0x0DE0,
	texture_2d = 0x0DE1,
	texture_3d = 0x806F,
	texture_1d_array = 0x8C18,
	texture_2d_array = 0x8C1A,
	texture_rectangle = 0x84F5,
	texture_cube_map = 0x8513,
	texture_cube_map_array = 0x9009,
	texture_2d_multisample = 0x9100,
	texture_2d_multisample_array = 0x9102,

	texture_cube_map_positive_x = 0x8515,
	texture_cube_map_positive_y = 0x8517,
	texture_cube_map_positive_z = 0x8519,
	texture_cube_map_negative_x = 0x8516,
	texture_cube_map_negative_y = 0x8518,
	texture_cube_map_negative_z = 0x851A
};

enum class InternalFormat : uint16_t {
	none = 0,
	r8 = 0x8229,
	r8_snorm = 0x8F94,
	r16 = 0x822A,
	r16_snorm = 0x8F98,
	rg8 = 0x822B,
	rg8_snorm = 0x8F95,
	rg16 = 0x822C,
	rg16_snorM = 0x8F99,
	r3_g3_b2 = 0x2A10,
	rgb4 = 0x804F,
	rgb5 = 0x8050,
	rgb8 = 0x8051,
	rgb8_snorM = 0x8F96,
	rgb10 = 0x8052,
	rgb12 = 0x8053,
	rgb16_snoRM = 0x8F9A,
	rgba2 = 0x8055,
	rgba4 = 0x8056,
	rgb5_a1 = 0x8057,
	rgba8 = 0x8058,
	rgba8_snoRM = 0x8F97,
	rgb10_a2 = 0x8059,
	rgb10_a2uI = 0x906F,
	rgba12 = 0x805A,
	rgba16 = 0x805B,
	srgb8 = 0x8C41,
	r16f = 0x822D,
	rg16f = 0x822F,
	rgb16f = 0x881B,
	rgba16f = 0x881A,
	r32f = 0x822E,
	rg32f = 0x8230,
	rgb32f = 0x8815,
	rgba32f = 0x8814,
	rgb9_e5 = 0x8C3D,
	r8i = 0x8231,
	r8ui = 0x8232,
	r16i = 0x8233,
	r16ui = 0x8234,
	r32i = 0x8235,
	r32ui = 0x8236,
	rg8i = 0x8237,
	rg8ui = 0x8238,
	rg16i = 0x8239,
	rg16ui = 0x823A,
	rg32i = 0x823B,
	rg32ui = 0x823C,
	rgb8i = 0x8D8F,
	rgb8ui = 0x8D7D,
	rgb16i = 0x8D89,
	rgb16ui = 0x8D77,
	rgb32i = 0x8D83,
	rgb32ui = 0x8D71,
	rgba8i = 0x8D8E,
	rgba8ui = 0x8D7C,
	rgba16i = 0x8D88,
	rgba16ui = 0x8D76,
	rgba32i = 0x8D82,
	rgba32ui = 0x8D70,
};

enum class Format : uint16_t {
	none = 0,
	r = 0x1903,
	rg = 0x8227,
	rgb = 0x1907,
	bgr = 0x80E0,
	rgba = 0x1908,
	bgra = 0x80E1,
	depth_component = 0x1902,
	stencil_index = 0x1901,
};

enum class DepthStencilMode : uint16_t {
	depth_component = 0x1902,
	stencil_index = 0x1901
};

enum class CompareFunc : uint16_t {
	lequal = 0x0203,
	gequal = 0x0206,
	less = 0x0201,
	greater = 0x0204,
	equal = 0x0202,
	notequal = 0x0205,
	always = 0x0207,
	never = 0x0200
};

enum class CompareMode : uint16_t {
	compare_ref_to_texture = 0x884E,
	none = 0
};

enum class MinFilter : uint16_t {
	nearest = 0x2600,
	linear = 0x2601,
	nearest_mipmap_nearest = 0x2700,
	linear_mipmap_nearest = 0x2701,
	nearest_mipmap_linear = 0x2702,
	linear_mipmap_linear = 0x2703
};

enum class MagFilter : uint16_t {
	nearest = 0x2600,
	linear = 0x2601
};

enum class Swizzle : uint16_t {
	red = 0x1903,
	green = 0x1904,
	blue = 0x1905,
	alpha = 0x1906,
	zero = 0,
	one = 1
};

enum class Wrap : uint16_t {
	clamp_to_edge = 0x812F,
	clamp_to_border = 0x812D,
	mirrored_repeat = 0x8370,
	repeat = 0x2901,
	mirror_clamp_to_edge = 0x8743
};

} // namespace void_engine::resource

#endif // VOID_ENGINE_RESOURCE_TEXTURE_ENUMS_HPP
