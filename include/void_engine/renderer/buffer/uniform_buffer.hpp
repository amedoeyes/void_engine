#ifndef VOID_ENGINE_RENDERER_BUFFER_UNIFORM_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_UNIFORM_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

namespace void_engine::renderer::buffer {

template <typename T>
class UniformBuffer final : public Buffer {
public:
	UniformBuffer() : Buffer(BufferTarget::uniform) {
	}

	void set_data(const T& data, BufferUsage usage = BufferUsage::dynamic_draw) {
		Buffer::set_data(data, usage);
	}

	template <typename U>
	void set_sub_data(unsigned int offset, const U& data) {
		Buffer::set_sub_data(offset, data);
	}

	void bind_range(unsigned int index, unsigned int offset = 0) const {
		Buffer::bind_range<T>(index, offset);
	}

	void update_data(const T& data) {
		Buffer::update_data(data);
	}
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFER_UNIFORM_BUFFER_HPP
