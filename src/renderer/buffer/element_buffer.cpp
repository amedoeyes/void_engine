#include "void_engine/renderer/buffer/element_buffer.hpp"

#include "void_engine/renderer/buffer/buffer.hpp"

#include <vector>

namespace void_engine::renderer::buffer {

ElementBuffer::ElementBuffer() : Buffer(BufferTarget::element_array) {
}

ElementBuffer::ElementBuffer(const std::vector<unsigned int>& indices, BufferUsage usage) :
	ElementBuffer() {
	set_data(indices, usage);
}

void ElementBuffer::set_data(const std::vector<unsigned int>& indices, BufferUsage usage) {
	Buffer::set_data(indices.size() * sizeof(unsigned int), indices.data(), usage);
	_count = indices.size();
}

auto ElementBuffer::get_count() const -> unsigned int {
	return _count;
}

} // namespace void_engine::renderer::buffer
