#ifndef VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_LAYOUT_HPP
#define VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_LAYOUT_HPP

#include "void_engine/renderer/vertex_array/vertex_array_attribute.hpp"

#include <cassert>
#include <glad/glad.h>
#include <vector>

namespace void_engine::renderer::vertex_array {

class VertexArrayLayout {
public:
	template <typename T>
	void add_attribute(unsigned int /*unused*/) {
		assert(false && "Unsupported type");
	}

	[[nodiscard]] auto get_attributes() const -> const std::vector<VertexArrayAttribute>&;

private:
	std::vector<VertexArrayAttribute> _attributes;
	unsigned int _size = 0;
};

template <>
void VertexArrayLayout::add_attribute<float>(unsigned int count);

template <>
void VertexArrayLayout::add_attribute<unsigned int>(unsigned int count);

} // namespace void_engine::renderer::vertex_array

#endif // !VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_LAYOUT_HPP
