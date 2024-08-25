#ifndef VOID_ENGINE_RENDERER_BUFFER_ARRAY_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_ARRAY_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

#include <vector>

namespace void_engine::renderer::buffer {

template <typename T>
class ArrayBuffer final : public Buffer {
public:
	ArrayBuffer() : Buffer(BufferTarget::array) {
	}
	explicit ArrayBuffer(unsigned int size, BufferUsage usage = BufferUsage::static_draw) :
		ArrayBuffer() {
		Buffer::allocate(size, usage);
	}
	explicit ArrayBuffer(
		const std::vector<T>& vertices, BufferUsage usage = BufferUsage::static_draw
	) :
		ArrayBuffer() {
		set_data(vertices, usage);
	}

	void set_data(const std::vector<T>& vertices, BufferUsage usage = BufferUsage::static_draw) {
		Buffer::set_data(vertices.size() * sizeof(T), vertices.data(), usage);
	}

	void update_data(const std::vector<T>& vertices) {
		Buffer::update_data(vertices.data());
	}
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFER_ARRAY_BUFFER_HPP
