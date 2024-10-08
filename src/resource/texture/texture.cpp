#include "void_engine/resource/texture/texture.hpp"

#include "void_engine/resource/texture/enums.hpp"

#include <cassert>
#include <cstddef>
#include <glad/glad.h>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace void_engine::resource::texture {

Texture::Texture(const Texture& other) : _target(other._target), _size(other._size) {
	glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
	switch (other._target) {
		case Target::texture_2d: set_texture_storage_2d(1, other._internal_format, _size); break;
		case Target::texture_3d:
		case Target::texture_2d_array: set_texture_storage_3d(1, other._internal_format, _size); break;
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
		other._size.z
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
		case Target::texture_2d: set_texture_storage_2d(1, other._internal_format, _size); break;
		case Target::texture_3d:
		case Target::texture_2d_array: set_texture_storage_3d(1, other._internal_format, _size); break;
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
		other._size.z
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

Texture::Texture(Target target) : _target(target) {
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

void Texture::bind_unit(unsigned int unit) const {
	glBindTextureUnit(unit, _id);
}

void Texture::set_texture_storage_2d(
	unsigned int levels, InternalFormat internal_format, const glm::ivec2& size
) {
	glTextureStorage2D(
		_id, static_cast<GLsizei>(levels), static_cast<GLenum>(internal_format), size.x, size.y
	);
	_size = glm::ivec3(size, 1.0f);
	_internal_format = internal_format;
}

void Texture::set_texture_storage_3d(
	unsigned int levels, InternalFormat internal_format, const glm::ivec3& size
) {
	glTextureStorage3D(
		_id, static_cast<GLsizei>(levels), static_cast<GLenum>(internal_format), size.x, size.y, size.z
	);
	_size = size;
	_internal_format = internal_format;
}

void Texture::set_sub_image_2d(
	unsigned int level, const glm::ivec2& offset, const glm::ivec2& size, Format format,
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

void Texture::set_sub_image_3d(
	unsigned int level, const glm::ivec3& offset, const glm::ivec3& size, Format format,
	const void* pixels
) const {
	glTextureSubImage3D(
		_id,
		static_cast<GLint>(level),
		offset.x,
		offset.y,
		offset.z,
		size.x,
		size.y,
		size.z,
		static_cast<GLenum>(format),
		GL_UNSIGNED_BYTE,
		pixels
	);
}

void Texture::generate_mipmap() const {
	glGenerateTextureMipmap(_id);
}

void Texture::set_depth_stencil_mode(DepthStencilMode mode) const {
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

void Texture::set_compare_func(CompareFunc func) const {
	glTextureParameteri(_id, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(func));
}

void Texture::set_compare_mode(CompareMode mode) const {
	glTextureParameteri(_id, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(mode));
}

void Texture::set_min_filter(MinFilter filter) const {
	glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
}

void Texture::set_mag_filter(MagFilter filter) const {
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

void Texture::set_swizzle_r(Swizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_R, static_cast<GLint>(swizzle));
}

void Texture::set_swizzle_g(Swizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_G, static_cast<GLint>(swizzle));
}

void Texture::set_swizzle_b(Swizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_B, static_cast<GLint>(swizzle));
}

void Texture::set_swizzle_a(Swizzle swizzle) const {
	glTextureParameteri(_id, GL_TEXTURE_SWIZZLE_A, static_cast<GLint>(swizzle));
}

void Texture::set_wrap_s(Wrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
}

void Texture::set_wrap_t(Wrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
}

void Texture::set_wrap_r(Wrap wrap) const {
	glTextureParameteri(_id, GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap));
}

auto Texture::get_data(Format format) const -> std::vector<std::byte> {
	std::vector<std::byte> data;
	data.resize(
		static_cast<decltype(data)::size_type>(_size.x) * _size.y * _size.z *
		get_bytes_per_pixel(format)
	);
	glGetTextureImage(
		_id,
		0,
		static_cast<GLenum>(format),
		GL_UNSIGNED_BYTE,
		static_cast<GLsizei>(data.size()),
		data.data()
	);
	return data;
}

auto Texture::get_size() const -> const glm::ivec3& {
	return _size;
}

auto Texture::get_bytes_per_pixel(Format format) -> unsigned int {
	switch (format) {
		using enum Format;
		case r: return 1;
		case rg: return 2;
		case rgb:
		case bgr: return 3;
		case rgba:
		case bgra: return 4;
		default: assert(false && "Not implemented");
	}
	return 0;
}

} // namespace void_engine::resource::texture
