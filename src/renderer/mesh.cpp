#include "void_engine/renderer/mesh.hpp"

#include "void_engine/renderer/buffer/element_buffer.hpp"
#include "void_engine/renderer/buffer/vertex_buffer.hpp"
#include "void_engine/renderer/renderer.hpp"

namespace void_engine::renderer {

Mesh::Mesh(
	vertex_array::VertexArray vao, buffer::VertexBuffer vbo, buffer::ElementBuffer ebo,
	PrimitiveType type
) :
	_vao(std::move(vao)),
	_vbo(std::move(vbo)),
	_ebo(std::move(ebo)),
	_type(type) {
}

void Mesh::draw() {
	_vao.bind();
	Renderer::draw_elements(_type, _ebo.get_count(), nullptr);
}

} // namespace void_engine::renderer
