#ifndef VOID_ENGINE_RESOURCES_TEXTURE_HPP
#define VOID_ENGINE_RESOURCES_TEXTURE_HPP

#include <glad/gl.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>

namespace void_engine::resources {

enum class TextureTarget {
	texture_1d = GL_TEXTURE_1D,
	texture_2d = GL_TEXTURE_2D,
	texture_3d = GL_TEXTURE_3D,
	texture_1d_array = GL_TEXTURE_1D_ARRAY,
	texture_2d_array = GL_TEXTURE_2D_ARRAY,
	texture_rectangle = GL_TEXTURE_RECTANGLE,
	texture_cube_map = GL_TEXTURE_CUBE_MAP,
	texture_cube_map_array = GL_TEXTURE_CUBE_MAP_ARRAY,
	texture_2d_multisample = GL_TEXTURE_2D_MULTISAMPLE,
	texture_2d_multisample_array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,

	texture_cube_map_positive_x = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	texture_cube_map_positive_y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	texture_cube_map_positive_z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	texture_cube_map_negative_x = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	texture_cube_map_negative_y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	texture_cube_map_negative_z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

enum class TextureDepthStencilMode {
	depth_component = GL_DEPTH_COMPONENT,
	stencil_index = GL_STENCIL_INDEX
};

enum class TextureCompareFunc {
	lequal = GL_LEQUAL,
	gequal = GL_GEQUAL,
	less = GL_LESS,
	greater = GL_GREATER,
	equal = GL_EQUAL,
	notequal = GL_NOTEQUAL,
	always = GL_ALWAYS,
	never = GL_NEVER
};

enum class TextureCompareMode {
	compare_ref_to_texture = GL_COMPARE_REF_TO_TEXTURE,
	none = GL_NONE
};

enum class TextureMinFilter {
	nearest = GL_NEAREST,
	linear = GL_LINEAR,
	nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
	linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
	nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
	linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR
};

enum class TextureMagFilter {
	nearest = GL_NEAREST,
	linear = GL_LINEAR
};

enum class TextureSwizzle {
	red = GL_RED,
	green = GL_GREEN,
	blue = GL_BLUE,
	alpha = GL_ALPHA,
	zero = GL_ZERO,
	one = GL_ONE
};

enum class TextureWrap {
	clamp_to_edge = GL_CLAMP_TO_EDGE,
	clamp_to_border = GL_CLAMP_TO_BORDER,
	mirrored_repeat = GL_MIRRORED_REPEAT,
	repeat = GL_REPEAT,
	mirror_clamp_to_edge = GL_MIRROR_CLAMP_TO_EDGE
};

class Texture {
public:
	Texture(TextureTarget target);
	~Texture();

public:
	auto bind() -> Texture*;
	void unbind() const;
	void activate(unsigned int slot = 0) const;

	auto generate_mipmap() -> Texture*;

	auto set_depth_stencil_mode(TextureDepthStencilMode mode) -> Texture*;

	auto set_base_level(int level) -> Texture*;

	auto set_border_color(glm::vec4 color) -> Texture*;

	auto set_compare_func(TextureCompareFunc func) -> Texture*;
	auto set_compare_mode(TextureCompareMode mode) -> Texture*;

	auto set_lod_bias(float bias) -> Texture*;

	auto set_min_filter(TextureMinFilter filter) -> Texture*;
	auto set_mag_filter(TextureMagFilter filter) -> Texture*;

	auto set_min_lod(float lod) -> Texture*;
	auto set_max_lod(float lod) -> Texture*;

	auto set_max_level(int level) -> Texture*;

	auto set_swizzle_r(TextureSwizzle swizzle) -> Texture*;
	auto set_swizzle_g(TextureSwizzle swizzle) -> Texture*;
	auto set_swizzle_b(TextureSwizzle swizzle) -> Texture*;
	auto set_swizzle_a(TextureSwizzle swizzle) -> Texture*;

	auto set_wrap_s(TextureWrap wrap) -> Texture*;
	auto set_wrap_t(TextureWrap wrap) -> Texture*;
	auto set_wrap_r(TextureWrap wrap) -> Texture*;

	void set_size(glm::vec2 size);
	[[nodiscard]] auto get_size() const -> glm::vec2;

private:
	TextureTarget _target;
	unsigned int _id;
	glm::vec2 _size;
};

} // namespace void_engine::resources

#endif // !#ifndef VOID_ENGINE_RESOURCES_TEXTURE_HPP
