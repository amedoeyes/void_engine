#include "void_engine/renderer/vertex_array/vertex_array_layout.hpp"

#include "void_engine/renderer/vertex_array/vertex_array_attribute.hpp"

#include <glad/glad.h>
#include <vector>

namespace void_engine::renderer::vertex_array {

auto VertexArrayLayout::get_attributes() const -> const std::vector<VertexArrayAttribute>& {
	return _attributes;
}

template <>
void VertexArrayLayout::add_attribute<float>(unsigned int count) {
	_attributes.push_back({count, _size, GL_FLOAT});
	_size += count * sizeof(float);
}

template <>
void VertexArrayLayout::add_attribute<unsigned int>(unsigned int count) {
	_attributes.push_back({count, _size, GL_UNSIGNED_INT});
	_size += count * sizeof(unsigned int);
}

} // namespace void_engine::renderer::vertex_array
