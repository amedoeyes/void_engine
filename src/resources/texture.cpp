#include "void_engine/resources/texture.hpp"

namespace void_engine::resources {

Texture::Texture(TextureTarget target) : _target(target) {
	glGenTextures(1, &_id);
}
Texture::~Texture() {
	glDeleteTextures(1, &_id);
}

auto Texture::bind() -> Texture* {
	glBindTexture(static_cast<int>(_target), _id);
	return this;
}
void Texture::unbind() const {
	glBindTexture(static_cast<int>(_target), 0);
}
void Texture::activate(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
}

auto Texture::generate_mipmap() -> Texture* {
	glGenerateMipmap(static_cast<int>(_target));
	return this;
}

auto Texture::set_depth_stencil_mode(TextureDepthStencilMode mode) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_DEPTH_STENCIL_TEXTURE_MODE,
		static_cast<int>(mode)
	);
	return this;
}

auto Texture::set_base_level(int level) -> Texture* {
	glTexParameteri(static_cast<int>(_target), GL_TEXTURE_BASE_LEVEL, level);
	return this;
}

auto Texture::set_border_color(glm::vec4 color) -> Texture* {
	glTexParameterfv(
		static_cast<int>(_target), GL_TEXTURE_BORDER_COLOR, &color[0]
	);
	return this;
}

auto Texture::set_compare_func(TextureCompareFunc func) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_COMPARE_FUNC,
		static_cast<int>(func)
	);
	return this;
}
auto Texture::set_compare_mode(TextureCompareMode mode) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_COMPARE_MODE,
		static_cast<int>(mode)
	);
	return this;
}

auto Texture::set_lod_bias(float bias) -> Texture* {
	glTexParameterf(static_cast<int>(_target), GL_TEXTURE_LOD_BIAS, bias);
	return this;
}

auto Texture::set_min_filter(TextureMinFilter filter) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_MIN_FILTER,
		static_cast<int>(filter)
	);
	return this;
}
auto Texture::set_mag_filter(TextureMagFilter filter) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_MAG_FILTER,
		static_cast<int>(filter)
	);
	return this;
}

auto Texture::set_min_lod(float lod) -> Texture* {
	glTexParameterf(static_cast<int>(_target), GL_TEXTURE_MIN_LOD, lod);
	return this;
}
auto Texture::set_max_lod(float lod) -> Texture* {
	glTexParameterf(static_cast<int>(_target), GL_TEXTURE_MAX_LOD, lod);
	return this;
}

auto Texture::set_max_level(int level) -> Texture* {
	glTexParameteri(static_cast<int>(_target), GL_TEXTURE_MAX_LEVEL, level);
	return this;
}

auto Texture::set_swizzle_r(TextureSwizzle swizzle) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_SWIZZLE_R,
		static_cast<int>(swizzle)
	);
	return this;
}
auto Texture::set_swizzle_g(TextureSwizzle swizzle) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_SWIZZLE_G,
		static_cast<int>(swizzle)
	);
	return this;
}
auto Texture::set_swizzle_b(TextureSwizzle swizzle) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_SWIZZLE_B,
		static_cast<int>(swizzle)
	);
	return this;
}
auto Texture::set_swizzle_a(TextureSwizzle swizzle) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_SWIZZLE_A,
		static_cast<int>(swizzle)
	);
	return this;
}

auto Texture::set_wrap_s(TextureWrap wrap) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_WRAP_S, static_cast<int>(wrap)
	);
	return this;
}
auto Texture::set_wrap_t(TextureWrap wrap) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_WRAP_T, static_cast<int>(wrap)
	);
	return this;
}
auto Texture::set_wrap_r(TextureWrap wrap) -> Texture* {
	glTexParameteri(
		static_cast<int>(_target), GL_TEXTURE_WRAP_R, static_cast<int>(wrap)
	);
	return this;
}

void Texture::set_size(glm::vec2 size) {
	_size = size;
}
auto Texture::get_size() const -> glm::vec2 {
	return _size;
}

} // namespace void_engine::resources
