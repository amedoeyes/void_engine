module;

#include <cassert>
#include <glad/glad.h>

module void_engine.graphics;

import :vertex_array;

import :buffer;
import :buffer.element;

namespace void_engine::graphics {

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

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind() const {
	glBindVertexArray(_id);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::set_divisor(unsigned int divisor) const {
	assert(_index > 0 && "No attributes added");
	glVertexArrayBindingDivisor(_id, _index - 1, divisor);
}

void VertexArray::set_element_buffer(const buffer::ElementBuffer& buffer) const {
	glVertexArrayElementBuffer(_id, buffer.get_id());
}

void VertexArray::add_attribute(unsigned int type, unsigned int count, unsigned int offset, bool normalized) {
	glEnableVertexArrayAttrib(_id, _index);
	glVertexArrayAttribFormat(_id, _index, static_cast<GLint>(count), type, static_cast<GLboolean>(normalized), offset);
	glVertexArrayAttribBinding(_id, _index, _buffer_index);
	_index++;
}

void VertexArray::add_vertex_buffer(const buffer::Buffer& buffer, unsigned int offset, unsigned int stride) {
	glVertexArrayVertexBuffer(_id, _buffer_index, buffer.get_id(), offset, static_cast<GLsizei>(stride));
	_buffer_index++;
}

} // namespace void_engine::graphics
