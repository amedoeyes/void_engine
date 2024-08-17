#ifndef VOID_ENGINE_RENDERER_MESH_HPP
#define VOID_ENGINE_RENDERER_MESH_HPP

#include "void_engine/renderer/buffer/element_buffer.hpp"
#include "void_engine/renderer/buffer/vertex_buffer.hpp"
#include "void_engine/renderer/vertex_array/vertex_array.hpp"

namespace void_engine::renderer {

enum class PrimitiveType;

struct Mesh {
	vertex_array::VertexArray vao;
	buffer::VertexBuffer vbo;
	buffer::ElementBuffer ebo;
	PrimitiveType type;
};

} // namespace void_engine::renderer

#endif // !VOID_ENGINE_RENDERER_MESH_HPP
