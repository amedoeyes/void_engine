#include "void_engine/renderer/buffer.hpp"

namespace void_engine::renderer {

Buffer::Buffer(BufferTarget target) :
	_target(static_cast<unsigned int>(target)) {
	glGenBuffers(1, &_id);
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

void Buffer::set_data(unsigned int size, const void* data, BufferUsage usage) {
	bind();
	glBufferData(_target, size, data, static_cast<unsigned int>(usage));
}

void Buffer::set_sub_data(
	unsigned int offset, unsigned int size, const void* data
) {
	bind();
	glBufferSubData(_target, offset, size, data);
}

auto Buffer::get_id() const -> unsigned int {
	return _id;
}

auto Buffer::get_count() const -> unsigned int {
	return _count;
}

void Buffer::set_count(unsigned int count) {
	_count = count;
}

} // namespace void_engine::renderer
