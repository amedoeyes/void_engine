#include "void_engine/renderer/buffer/vertex_buffer.hpp"

#include "void_engine/renderer/buffer/buffer.hpp"

namespace void_engine::renderer::buffer {

VertexBuffer::VertexBuffer() : Buffer(BufferTarget::array) {
}

auto VertexBuffer::get_size() const -> unsigned int {
	return _size;
}

} // namespace void_engine::renderer::buffer
