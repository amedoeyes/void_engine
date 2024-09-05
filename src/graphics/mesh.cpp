#include "void_engine/graphics/mesh.hpp"

#include "void_engine/graphics/buffer/buffer.hpp"
#include "void_engine/graphics/buffer/element_buffer.hpp"
#include "void_engine/graphics/renderer/enums.hpp"
#include "void_engine/graphics/vertex_array.hpp"

#include <utility>
#include <vector>

namespace void_engine::graphics {

Mesh::Mesh(const Mesh& other) :
	_vertex_array(new VertexArray(*other._vertex_array)),
	_element_buffer(new buffer::ElementBuffer(*other._element_buffer)),
	_primitive_type(other._primitive_type) {
	for (const auto* buffer : other._vertex_buffers) {
		_vertex_buffers.push_back(new buffer::Buffer(*buffer));
	}
}

Mesh::Mesh(Mesh&& other) noexcept :
	_vertex_array(other._vertex_array),
	_vertex_buffers(std::move(other._vertex_buffers)),
	_element_buffer(other._element_buffer),
	_primitive_type(other._primitive_type) {
	other._vertex_array = nullptr;
	other._element_buffer = nullptr;
}

auto Mesh::operator=(const Mesh& other) -> Mesh& {
	if (this == &other) {
		return *this;
	}
	delete _vertex_array;
	delete _element_buffer;
	for (const auto* buffer : _vertex_buffers) {
		delete buffer;
	}
	_vertex_array = new VertexArray(*other._vertex_array);
	_element_buffer = new buffer::ElementBuffer(*other._element_buffer);
	for (const auto* buffer : other._vertex_buffers) {
		_vertex_buffers.push_back(new buffer::Buffer(*buffer));
	}
	_primitive_type = other._primitive_type;
	return *this;
}

auto Mesh::operator=(Mesh&& other) noexcept -> Mesh& {
	if (this == &other) {
		return *this;
	}
	delete _vertex_array;
	delete _element_buffer;
	for (const auto* buffer : _vertex_buffers) {
		delete buffer;
	}
	_vertex_array = other._vertex_array;
	_vertex_buffers = std::move(other._vertex_buffers);
	_element_buffer = other._element_buffer;
	_primitive_type = other._primitive_type;
	other._vertex_array = nullptr;
	other._element_buffer = nullptr;
	return *this;
}

Mesh::Mesh() :
	_vertex_array(new VertexArray()),
	_element_buffer(new buffer::ElementBuffer()),
	_primitive_type(PrimitiveType::triangles) {
	_vertex_array->set_element_buffer(*_element_buffer);
}

Mesh::Mesh(PrimitiveType primitive_type) :
	_vertex_array(new VertexArray()),
	_element_buffer(new buffer::ElementBuffer()),
	_primitive_type(primitive_type) {
	_vertex_array->set_element_buffer(*_element_buffer);
}

Mesh::~Mesh() {
	delete _vertex_array;
	delete _element_buffer;
	for (const auto* buffer : _vertex_buffers) {
		delete buffer;
	}
}

void Mesh::bind() const {
	_vertex_array->bind();
}

void Mesh::unbind() {
	VertexArray::unbind();
}

void Mesh::set_divisor(unsigned int divisor) const {
	_vertex_array->set_divisor(divisor);
}

void Mesh::set_indices(const std::vector<unsigned int>& data, buffer::BufferUsage usage) {
	_element_buffer->set_data(data, usage);
}

void Mesh::set_primitive_type(PrimitiveType primitive) {
	_primitive_type = primitive;
}

auto Mesh::get_vertex_array() -> VertexArray& {
	return *_vertex_array;
}

auto Mesh::get_vertex_array() const -> const VertexArray& {
	return *_vertex_array;
}

auto Mesh::get_element_buffer() -> buffer::ElementBuffer& {
	return *_element_buffer;
}

auto Mesh::get_element_buffer() const -> const buffer::ElementBuffer& {
	return *_element_buffer;
}

auto Mesh::get_primitive_type() const -> PrimitiveType {
	return _primitive_type;
}

auto Mesh::get_count() const -> unsigned int {
	return _element_buffer->get_count();
}

} // namespace void_engine::graphics
