#include "void_engine/renderer/vertex_array.hpp"

#include "void_engine/renderer/buffer.hpp"

#include <glad/gl.h>

namespace void_engine::renderer {

VertexArray::VertexArray() : _vertex_buffer(BufferTarget::array) {
	glCreateVertexArrays(1, &_id);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind() const {
	glBindVertexArray(_id);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::set_vertex_buffer(
	unsigned int size, const void* data, BufferUsage usage
) {
	_vertex_buffer.set_data(size, data, usage);
}

void VertexArray::add_buffer(int size, int stride, unsigned int offset) {
	glVertexArrayVertexBuffer(
		_id, _index, _vertex_buffer.get_id(), offset, stride
	);
	glVertexArrayAttribFormat(_id, _index, size, GL_FLOAT, false, 0);
	glVertexArrayAttribBinding(_id, _index, _index);
	glEnableVertexArrayAttrib(_id, _index);
	_index++;
}

} // namespace void_engine::renderer
