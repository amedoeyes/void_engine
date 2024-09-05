#include "void_engine/graphics/buffer/element_buffer.hpp"

#include "void_engine/graphics/buffer/buffer.hpp"

#include <vector>

namespace void_engine::graphics::buffer {

ElementBuffer::ElementBuffer() : Buffer(BufferTarget::element_array) {
}

ElementBuffer::ElementBuffer(unsigned int size, BufferUsage usage) : ElementBuffer() {
	Buffer::allocate(size, usage);
}

ElementBuffer::ElementBuffer(const std::vector<unsigned int>& indices, BufferUsage usage) :
	ElementBuffer() {
	set_data(indices, usage);
}

void ElementBuffer::set_data(const std::vector<unsigned int>& indices, BufferUsage usage) {
	Buffer::set_data(indices.size() * sizeof(unsigned int), indices.data(), usage);
	_count = indices.size();
}

void ElementBuffer::update_data(const std::vector<unsigned int>& indices) {
	Buffer::update_data(indices.data());
	_count = indices.size();
}

auto ElementBuffer::get_count() const -> unsigned int {
	return _count;
}

} // namespace void_engine::graphics::buffer
