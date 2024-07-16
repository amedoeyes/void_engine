#include "void_engine/resource/texture/texture.hpp"

#include <glad/glad.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace void_engine::resource {

Texture::Texture(TextureTarget target) : _target(target) {
	glCreateTextures(static_cast<int>(_target), 1, &_id);
}

Texture::~Texture() {
	glDeleteTextures(1, &_id);
}

void Texture::bind() const {
	glBindTexture(static_cast<int>(_target), _id);
}

void Texture::unbind() const {
	glBindTexture(static_cast<int>(_target), 0);
}

void Texture::bind_unit(unsigned int unit) const {
	glBindTextureUnit(unit, _id);
}

void Texture::set_texture_storage_2d(
	unsigned int levels, TextureInternalFormat internal_format, const glm::vec2& size
) {
	glTextureStorage2D(
		_id,
		static_cast<int>(levels),
		static_cast<int>(internal_format),
		static_cast<int>(size.x),
		static_cast<int>(size.y)
	);
	_size = size;
}

void Texture::set_sub_image_2d(
	unsigned int level, const glm::vec2& offset, const glm::vec2& size, TextureFormat format,
	const void* pixels
) const {
	glTextureSubImage2D(
		_id,
		static_cast<int>(level),
		static_cast<int>(offset.x),
		static_cast<int>(offset.y),
		static_cast<int>(size.x),
		static_cast<int>(size.y),
		static_cast<int>(format),
		GL_UNSIGNED_BYTE,
		pixels
	);
}

void Texture::generate_mipmap() const {
	glGenerateTextureMipmap(_id);
}

void Texture::set_depth_stencil_mode(TextureDepthStencilMode mode) const {
	glTextureParameteri(_id, GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<int>(mode));
}

void Texture::set_base_level(int level) const {
	glTextureParameteri(_id, GL_TEXTURE_BASE_LEVEL, level);
}

void Texture::set_max_level(int level) const {
	glTextureParameteri(_id, GL_TEXTURE_MAX_LEVEL, level);
}

void Texture::set_border_color(const glm::vec4& color) const {
	glTextureParameterfv(_id, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(color));
}

void Texture::set_compare_func(TextureCompareFunc func) const {
	glTextureParameteri(_id, GL_TEXTURE_COMPARE_FUNC, static_cast<int>(func));
}

void Texture::set_compare_mode(TextureCompareMode mode) const {
	glTextureParameteri(_id, GL_TEXTURE_COMPARE_MODE, static_cast<int>(mode));
}

void Texture::set_min_filter(TextureMinFilter filter) const {
	glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, static_cast<int>(filter));
}

void Texture::set_mag_filter(TextureMagFilter filter) const {
	glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, static_cast<int>(filter));
}

void Texture::set_min_lod(float lod) const {
	glTextureParameterf(_id, GL_TEXTURE_MIN_LOD, lod);
}

void Texture::set_max_lod(float lod) const {
	glTextureParameterf(_id, GL_TEXTURE_MAX_LOD, lod);
}

void Texture::set_lod_bias(float bias) const {
	glTextureParameterf(_id, GL_TEXTURE_LOD_BIAS, bias);
}

void Texture::set_swizzle_r(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_R, static_cast<int>(swizzle));
}

void Texture::set_swizzle_g(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_G, static_cast<int>(swizzle));
}

void Texture::set_swizzle_b(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_B, static_cast<int>(swizzle));
}

void Texture::set_swizzle_a(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_A, static_cast<int>(swizzle));
}

void Texture::set_wrap_s(TextureWrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_S, static_cast<int>(wrap));
}

void Texture::set_wrap_t(TextureWrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_T, static_cast<int>(wrap));
}

void Texture::set_wrap_r(TextureWrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_R, static_cast<int>(wrap));
}

auto Texture::get_size() const -> const glm::vec2& {
	return _size;
}

} // namespace void_engine::resource
