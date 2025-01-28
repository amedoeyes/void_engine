module;

#include <cassert>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

module void_engine.graphics;

import std;
import glm;
import void_engine.resources;

namespace void_engine::graphics {

Texture::Texture(const Texture& other) : _target(other._target), _size(other._size) {
	glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
	switch (other._target) {
		case TextureTarget::texture_2d: set_texture_storage_2d(1, other._internal_format, _size); break;
		case TextureTarget::texture_3d:
		case TextureTarget::texture_2d_array:
			set_texture_storage_3d(1, other._internal_format, _size);
			break;
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
		case TextureTarget::texture_2d: set_texture_storage_2d(1, other._internal_format, _size); break;
		case TextureTarget::texture_3d:
		case TextureTarget::texture_2d_array:
			set_texture_storage_3d(1, other._internal_format, _size);
			break;
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

Texture::Texture(TextureTarget target) : _target(target) {
	glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
}

Texture::Texture(TextureTarget target, const std::filesystem::path& path) : Texture(target) {
	switch (_target) {
		using enum TextureTarget;
		case texture_2d: {
			const auto image = resources::Image(path, true);
			set_texture_storage_2d(1, TextureInternalFormat::rgba8, image.get_size());
			TextureFormat format = TextureFormat::none;
			switch (image.get_color_type()) {
				using enum resources::ColorType;
				case gray: format = TextureFormat::r; break;
				case gray_alpha: format = TextureFormat::rg; break;
				case rgb: format = TextureFormat::rgb; break;
				case rgba: format = TextureFormat::rgba; break;
				default: std::unreachable();
			}
			set_sub_image_2d(0, {0, 0}, image.get_size(), format, image.get_data().data());
			break;
		}
		default: break;
	}
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
	unsigned int levels, TextureInternalFormat internal_format, const glm::ivec2& size
) {
	glTextureStorage2D(
		_id, static_cast<GLsizei>(levels), static_cast<GLenum>(internal_format), size.x, size.y
	);
	_size = glm::ivec3(size, 1.0f);
	_internal_format = internal_format;
}

void Texture::set_texture_storage_3d(
	unsigned int levels, TextureInternalFormat internal_format, const glm::ivec3& size
) {
	glTextureStorage3D(
		_id, static_cast<GLsizei>(levels), static_cast<GLenum>(internal_format), size.x, size.y, size.z
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

void Texture::set_sub_image_3d(
	unsigned int level, const glm::ivec3& offset, const glm::ivec3& size, TextureFormat format,
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

auto Texture::get_data(TextureFormat format) const -> std::vector<std::byte> {
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

auto Texture::get_bytes_per_pixel(TextureFormat format) -> unsigned int {
	switch (format) {
		using enum TextureFormat;
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

} // namespace void_engine::graphics
