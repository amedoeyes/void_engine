#include "void_engine/resource/texture/texture.hpp"

#include "void_engine/resource/texture/enums.hpp"

#include <cassert>
#include <glad/glad.h>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace void_engine::resource {

Texture::Texture(const Texture& other) : _target(other._target), _size(other._size) {
	glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
	switch (other._target) {
		case TextureTarget::texture_2d: set_texture_storage_2d(1, other._internal_format, _size); break;
		default: assert(false && "Not implemented");
	}
	glCopyImageSubData(
		other._id,
		static_cast<GLenum>(other._target),
		0,
		0,
		0,
		0,
		_id,
		static_cast<GLenum>(_target),
		0,
		0,
		0,
		0,
		other._size.x,
		other._size.y,
		1
	);
}

Texture::Texture(Texture&& other) noexcept :
	_id(other._id),
	_target(other._target),
	_size(other._size),
	_internal_format(other._internal_format) {
	other._id = 0;
}

auto Texture::operator=(const Texture& other) -> Texture& {
	if (this == &other) {
		return *this;
	}
	_target = other._target;
	_size = other._size;
	glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
	switch (other._target) {
		case TextureTarget::texture_2d: set_texture_storage_2d(1, other._internal_format, _size); break;
		default: assert(false && "Not implemented");
	}
	glCopyImageSubData(
		other._id,
		static_cast<GLenum>(other._target),
		0,
		0,
		0,
		0,
		_id,
		static_cast<GLenum>(_target),
		0,
		0,
		0,
		0,
		other._size.x,
		other._size.y,
		1
	);
	return *this;
}

auto Texture::operator=(Texture&& other) noexcept -> Texture& {
	if (this == &other) {
		return *this;
	}
	_id = other._id;
	_target = other._target;
	_size = other._size;
	_internal_format = other._internal_format;
	other._id = 0;
	return *this;
}

Texture::Texture(TextureTarget target) : _target(target) {
	glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
}

Texture::~Texture() {
	if (_id == 0) {
		return;
	}
	glDeleteTextures(1, &_id);
}

void Texture::bind() const {
	glBindTexture(static_cast<GLenum>(_target), _id);
}

void Texture::unbind() const {
	glBindTexture(static_cast<GLenum>(_target), 0);
}

auto Texture::bind_unit(unsigned int unit) const -> int {
	glBindTextureUnit(unit, _id);
	return static_cast<int>(unit);
}

void Texture::set_texture_storage_2d(
	unsigned int levels, TextureInternalFormat internal_format, const glm::ivec2& size
) {
	glTextureStorage2D(
		_id, static_cast<GLsizei>(levels), static_cast<GLenum>(internal_format), size.x, size.y
	);
	_size = size;
	_internal_format = internal_format;
}

void Texture::set_sub_image_2d(
	unsigned int level, const glm::ivec2& offset, const glm::ivec2& size, TextureFormat format,
	const void* pixels
) const {
	glTextureSubImage2D(
		_id,
		static_cast<GLint>(level),
		offset.x,
		offset.y,
		size.x,
		size.y,
		static_cast<GLenum>(format),
		GL_UNSIGNED_BYTE,
		pixels
	);
}

void Texture::generate_mipmap() const {
	glGenerateTextureMipmap(_id);
}

void Texture::set_depth_stencil_mode(TextureDepthStencilMode mode) const {
	glTextureParameteri(_id, GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<GLint>(mode));
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
	glTextureParameteri(_id, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(func));
}

void Texture::set_compare_mode(TextureCompareMode mode) const {
	glTextureParameteri(_id, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(mode));
}

void Texture::set_min_filter(TextureMinFilter filter) const {
	glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
}

void Texture::set_mag_filter(TextureMagFilter filter) const {
	glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
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
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_R, static_cast<GLint>(swizzle));
}

void Texture::set_swizzle_g(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_G, static_cast<GLint>(swizzle));
}

void Texture::set_swizzle_b(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_B, static_cast<GLint>(swizzle));
}

void Texture::set_swizzle_a(TextureSwizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_A, static_cast<GLint>(swizzle));
}

void Texture::set_wrap_s(TextureWrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
}

void Texture::set_wrap_t(TextureWrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
}

void Texture::set_wrap_r(TextureWrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap));
}

auto Texture::get_size() const -> const glm::ivec2& {
	return _size;
}

} // namespace void_engine::resource
