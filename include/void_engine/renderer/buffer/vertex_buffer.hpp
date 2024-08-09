#ifndef VOID_ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

#include <vector>

namespace void_engine::renderer::buffer {

class VertexBuffer final : public Buffer {
public:
	VertexBuffer();

	template <typename VertexType>
	explicit VertexBuffer(
		const std::vector<VertexType>& vertices, BufferUsage usage = BufferUsage::static_draw
	) :
		VertexBuffer() {
		set_data(vertices, usage);
	}

	template <typename VertexType>
	void set_data(
		const std::vector<VertexType>& vertices, BufferUsage usage = BufferUsage::static_draw
	) {
		Buffer::set_data(vertices.size() * sizeof(VertexType), vertices.data(), usage);
		_size = sizeof(VertexType);
	}

	[[nodiscard]] auto get_size() const -> unsigned int;

private:
	unsigned int _size = 0;
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP
