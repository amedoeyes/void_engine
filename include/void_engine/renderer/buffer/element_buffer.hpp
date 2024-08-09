#ifndef VOID_ENGINE_RENDERER_BUFFERS_ELEMENT_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFERS_ELEMENT_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

#include <vector>

namespace void_engine::renderer::buffer {

class ElementBuffer final : public Buffer {
public:
	ElementBuffer();
	explicit ElementBuffer(
		const std::vector<unsigned int>& indices, BufferUsage usage = BufferUsage::static_draw
	);

	void set_data(
		const std::vector<unsigned int>& indices, BufferUsage usage = BufferUsage::static_draw
	);

	[[nodiscard]] auto get_count() const -> unsigned int;

private:
	unsigned int _count = 0;
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFERS_ELEMENT_BUFFER_HPP
