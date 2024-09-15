#include "void_engine/graphics/buffer/buffer.hpp"

#include <glad/glad.h>

namespace void_engine::graphics::buffer {

Buffer::Buffer(const Buffer& other) :
	_target(other._target),
	_usage(other._usage),
	_allocated_size(other._allocated_size) {
	GLint size = 0;
	GLint usage = 0;
	glGetNamedBufferParameteriv(other._id, GL_BUFFER_SIZE, &size);
	glGetNamedBufferParameteriv(other._id, GL_BUFFER_USAGE, &usage);
	glCreateBuffers(1, &_id);
	glNamedBufferData(_id, size, nullptr, usage);
	glCopyNamedBufferSubData(other._id, _id, 0, 0, size);
}

Buffer::Buffer(Buffer&& other) noexcept :
	_id(other._id),
	_target(other._target),
	_usage(other._usage),
	_allocated_size(other._allocated_size) {
	other._id = 0;
	other._allocated_size = 0;
}

auto Buffer::operator=(const Buffer& other) -> Buffer& {
	if (this == &other) {
		return *this;
	}
	if (_id != 0) {
		glDeleteBuffers(1, &_id);
	}
	_target = other._target;
	_usage = other._usage;
	_allocated_size = other._allocated_size;
	GLint size = 0;
	GLint usage = 0;
	glGetNamedBufferParameteriv(other._id, GL_BUFFER_SIZE, &size);
	glGetNamedBufferParameteriv(other._id, GL_BUFFER_USAGE, &usage);
	glCreateBuffers(1, &_id);
	glNamedBufferData(_id, size, nullptr, usage);
	glCopyNamedBufferSubData(other._id, _id, 0, 0, size);
	return *this;
}

auto Buffer::operator=(Buffer&& other) noexcept -> Buffer& {
	if (_id != 0) {
		glDeleteBuffers(1, &_id);
	}
	_id = other._id;
	_target = other._target;
	_usage = other._usage;
	_allocated_size = other._allocated_size;
	other._id = 0;
	other._allocated_size = 0;
	return *this;
}

Buffer::Buffer(BufferTarget target) : _target(target) {
	glCreateBuffers(1, &_id);
}

Buffer::~Buffer() {
	if (_id == 0) {
		return;
	}
	glDeleteBuffers(1, &_id);
}

void Buffer::bind() const {
	glBindBuffer(static_cast<GLenum>(_target), _id);
}

void Buffer::unbind() const {
	glBindBuffer(static_cast<GLenum>(_target), 0);
}

void Buffer::allocate(unsigned int size, BufferUsage usage) {
	glNamedBufferData(_id, size, nullptr, static_cast<GLenum>(usage));
	_allocated_size = size;
	_usage = usage;
}

void Buffer::set_data(unsigned int size, const void* data, BufferUsage usage) {
	glNamedBufferData(_id, size, data, static_cast<GLenum>(usage));
	_allocated_size = size;
	_usage = usage;
}

void Buffer::set_sub_data(unsigned int offset, unsigned int size, const void* data) const {
	glNamedBufferSubData(_id, offset, size, data);
}

void Buffer::update_data(const void* data) const {
	glNamedBufferSubData(_id, 0, _allocated_size, data);
}

void Buffer::bind_range(unsigned int index, unsigned int offset, unsigned int size) const {
	glBindBufferRange(static_cast<GLenum>(_target), index, _id, offset, size);
}

auto Buffer::get_id() const -> unsigned int {
	return _id;
}

} // namespace void_engine::graphics::buffer
