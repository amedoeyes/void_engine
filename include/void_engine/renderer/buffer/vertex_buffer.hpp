#ifndef VOID_ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

#include <vector>

namespace void_engine::renderer::buffer {

class VertexBuffer final : public Buffer {
public:
	VertexBuffer() : Buffer(BufferTarget::array) {
	}

	template <typename VertexType>
	VertexBuffer(const std::vector<VertexType>& vertices, BufferUsage usage) : VertexBuffer() {
		set_data(vertices, usage);
	}

	template <typename VertexType>
	void set_data(const std::vector<VertexType>& vertices, BufferUsage usage) {
		Buffer::set_data(vertices.size() * sizeof(VertexType), vertices.data(), usage);
	}
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP
