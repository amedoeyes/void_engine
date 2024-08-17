#include "void_engine/renderer/buffer/buffer.hpp"

#include <glad/glad.h>

namespace void_engine::renderer::buffer {

Buffer::Buffer(const Buffer& other) {
	_target = other._target;
	GLint size = 0;
	GLint usage = 0;
	glGetNamedBufferParameteriv(other._id, GL_BUFFER_SIZE, &size);
	glGetNamedBufferParameteriv(other._id, GL_BUFFER_USAGE, &usage);
	glCreateBuffers(1, &_id);
	glNamedBufferData(_id, size, nullptr, usage);
	glCopyNamedBufferSubData(other._id, _id, 0, 0, size);
}

Buffer::Buffer(Buffer&& other) noexcept : _id(other._id), _target(other._target) {
	other._id = 0;
}

auto Buffer::operator=(const Buffer& other) -> Buffer& {
	if (this == &other) {
		return *this;
	}
	if (_id != 0) {
		glDeleteBuffers(1, &_id);
	}
	_target = other._target;
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
	if (this == &other) {
		return *this;
	}
	if (_id != 0) {
		glDeleteBuffers(1, &_id);
	}
	_id = other._id;
	_target = other._target;
	other._id = 0;
	return *this;
}

Buffer::Buffer(BufferTarget target) : _target(static_cast<unsigned int>(target)) {
	glCreateBuffers(1, &_id);
}

Buffer::~Buffer() {
	glDeleteBuffers(1, &_id);
}

void Buffer::bind() const {
	glBindBuffer(_target, _id);
}

void Buffer::unbind() const {
	glBindBuffer(_target, 0);
}

void Buffer::allocate(unsigned int size, BufferUsage usage) {
	glNamedBufferData(_id, size, nullptr, static_cast<GLenum>(usage));
	_allocated_size = size;
}

void Buffer::set_data(unsigned int size, const void* data, BufferUsage usage) {
	glNamedBufferData(_id, size, data, static_cast<GLenum>(usage));
	_allocated_size = size;
}

void Buffer::set_sub_data(unsigned int offset, unsigned int size, const void* data) const {
	glNamedBufferSubData(_id, offset, size, data);
}

void Buffer::bind_buffer_range(unsigned int index, unsigned int offset, unsigned int size) const {
	glBindBufferRange(_target, index, _id, offset, size);
}

auto Buffer::get_id() const -> unsigned int {
	return _id;
}

} // namespace void_engine::renderer::buffer
