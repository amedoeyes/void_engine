#include "void_engine/renderer/buffer/buffer.hpp"

#include <glad/glad.h>

namespace void_engine::renderer::buffer {

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

void Buffer::set_data(unsigned int size, const void* data, BufferUsage usage) const {
	glNamedBufferData(_id, size, data, static_cast<unsigned int>(usage));
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
