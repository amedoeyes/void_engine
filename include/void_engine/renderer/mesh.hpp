#ifndef VOID_ENGINE_RENDERER_MESH_HPP
#define VOID_ENGINE_RENDERER_MESH_HPP

#include "void_engine/renderer/buffer/element_buffer.hpp"
#include "void_engine/renderer/buffer/vertex_buffer.hpp"
#include "void_engine/renderer/renderer.hpp"
#include "void_engine/renderer/vertex_array/vertex_array.hpp"

namespace void_engine::renderer {

class Mesh {
public:
	Mesh(const Mesh&) = default;
	Mesh(Mesh&&) = default;
	auto operator=(const Mesh&) -> Mesh& = default;
	auto operator=(Mesh&&) -> Mesh& = default;
	Mesh() = delete;
	Mesh(
		vertex_array::VertexArray vao, buffer::VertexBuffer vbo, buffer::ElementBuffer ebo,
		PrimitiveType type
	);
	~Mesh() = default;

	void draw();

private:
	vertex_array::VertexArray _vao;
	buffer::VertexBuffer _vbo;
	buffer::ElementBuffer _ebo;
	PrimitiveType _type;
};

} // namespace void_engine::renderer

#endif // !VOID_ENGINE_RENDERER_MESH_HPP
