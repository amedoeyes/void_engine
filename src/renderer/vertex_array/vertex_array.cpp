#include "void_engine/renderer/vertex_array/vertex_array.hpp"

#include "void_engine/renderer/buffer/element_buffer.hpp"
#include "void_engine/renderer/vertex_array/vertex_array_layout.hpp"

#include <cstddef>
#include <glad/glad.h>

namespace void_engine::renderer::vertex_array {

VertexArray::VertexArray(const VertexArray& other) {
	glCreateVertexArrays(1, &_id);
	GLint max_bindings = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_bindings);
	for (int i = 0; i < max_bindings; ++i) {
		GLint buffer = 0;
		glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_BUFFER, &buffer);
		if (buffer != 0) {
			GLint offset = 0;
			GLint stride = 0;
			GLint divisor = 0;
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_OFFSET, &offset);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_STRIDE, &stride);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_DIVISOR, &divisor);
			glVertexArrayVertexBuffer(_id, i, buffer, offset, stride);
			glVertexArrayBindingDivisor(_id, i, divisor);
		}
	}
	GLint max_attribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);
	for (int i = 0; i < max_attribs; ++i) {
		GLint enabled = 0;
		glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
		if (enabled != 0) {
			GLint buffer = 0;
			GLint size = 0;
			GLint type = 0;
			GLint normalized = 0;
			GLint stride = 0;
			GLint offset = 0;
			GLint binding = 0;
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &buffer);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_RELATIVE_OFFSET, &offset);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_BINDING, &binding);
			glEnableVertexArrayAttrib(_id, i);
			glVertexArrayAttribFormat(_id, i, size, type, normalized, offset);
			glVertexArrayAttribBinding(_id, i, binding);
		}
	}
	GLint element_buffer = 0;
	glGetVertexArrayiv(other._id, GL_ELEMENT_ARRAY_BUFFER_BINDING, &element_buffer);
	if (element_buffer != 0) {
		glVertexArrayElementBuffer(_id, element_buffer);
	}
}

VertexArray::VertexArray(VertexArray&& other) noexcept : _id(other._id) {
	other._id = 0;
}

auto VertexArray::operator=(const VertexArray& other) -> VertexArray& {
	if (this == &other) {
		return *this;
	}
	if (_id != 0) {
		glDeleteVertexArrays(1, &_id);
	}
	glCreateVertexArrays(1, &_id);
	GLint max_bindings = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_bindings);
	for (int i = 0; i < max_bindings; ++i) {
		GLint buffer = 0;
		glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_BUFFER, &buffer);
		if (buffer != 0) {
			GLint offset = 0;
			GLint stride = 0;
			GLint divisor = 0;
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_OFFSET, &offset);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_STRIDE, &stride);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_BINDING_DIVISOR, &divisor);
			glVertexArrayVertexBuffer(_id, i, buffer, offset, stride);
			glVertexArrayBindingDivisor(_id, i, divisor);
		}
	}
	GLint max_attribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);
	for (int i = 0; i < max_attribs; ++i) {
		GLint enabled = 0;
		glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
		if (enabled != 0) {
			GLint buffer = 0;
			GLint size = 0;
			GLint type = 0;
			GLint normalized = 0;
			GLint stride = 0;
			GLint offset = 0;
			GLint binding = 0;
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &buffer);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_RELATIVE_OFFSET, &offset);
			glGetVertexArrayIndexediv(other._id, i, GL_VERTEX_ATTRIB_BINDING, &binding);
			glEnableVertexArrayAttrib(_id, i);
			glVertexArrayAttribFormat(_id, i, size, type, normalized, offset);
			glVertexArrayAttribBinding(_id, i, binding);
		}
	}
	GLint element_buffer = 0;
	glGetVertexArrayiv(other._id, GL_ELEMENT_ARRAY_BUFFER_BINDING, &element_buffer);
	if (element_buffer != 0) {
		glVertexArrayElementBuffer(_id, element_buffer);
	}
	return *this;
}

auto VertexArray::operator=(VertexArray&& other) noexcept -> VertexArray& {
	if (this == &other) {
		return *this;
	}
	if (_id != 0) {
		glDeleteVertexArrays(1, &_id);
	}
	_id = other._id;
	other._id = 0;
	return *this;
}

VertexArray::VertexArray() {
	glCreateVertexArrays(1, &_id);
}

VertexArray::VertexArray(const VertexArrayLayout& layout) : VertexArray() {
	set_layout(layout);
}

VertexArray::VertexArray(
	const VertexArrayLayout& layout, const buffer::VertexBuffer& vertex_buffer,
	const buffer::ElementBuffer& element_buffer
) :
	VertexArray(layout) {
	set_vertex_buffer(vertex_buffer);
	set_element_buffer(element_buffer);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind() const {
	glBindVertexArray(_id);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(
	const buffer::VertexBuffer& buffer, unsigned int index, unsigned int offset, unsigned int stride
) const {
	glVertexArrayVertexBuffer(_id, index, buffer.get_id(), offset, static_cast<GLsizei>(stride));
}

void VertexArray::set_vertex_buffer(const buffer::VertexBuffer& buffer) const {
	add_vertex_buffer(buffer, 0, 0, buffer.get_size());
}

void VertexArray::set_element_buffer(const buffer::ElementBuffer& buffer) const {
	glVertexArrayElementBuffer(_id, buffer.get_id());
}

void VertexArray::add_attribute(
	unsigned int index, unsigned int count, unsigned int offset, unsigned int type, bool normalized
) const {
	glEnableVertexArrayAttrib(_id, index);
	glVertexArrayAttribFormat(
		_id, index, static_cast<GLint>(count), type, static_cast<GLboolean>(normalized), offset
	);
	glVertexArrayAttribBinding(_id, index, 0);
}

void VertexArray::set_layout(const VertexArrayLayout& layout) const {
	const auto& attributes = layout.get_attributes();
	for (size_t i = 0; i < attributes.size(); ++i) {
		const auto& attribute = attributes[i];
		add_attribute(i, attribute.count, attribute.stride, attribute.type, attribute.normalized);
	}
}

} // namespace void_engine::renderer::vertex_array
