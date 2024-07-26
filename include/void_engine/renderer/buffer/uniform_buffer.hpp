#ifndef VOID_ENGINE_RENDERER_BUFFERS_UNIFORM_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFERS_UNIFORM_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

namespace void_engine::renderer::buffer {

template <typename UniformType>
class UniformBuffer final : public Buffer {
public:
	UniformBuffer(unsigned int index, const UniformType& data, BufferUsage usage) :
		Buffer(BufferTarget::uniform) {
		set_data(data, usage);
		Buffer::bind_buffer_range(index, 0, sizeof(UniformType));
	}

	void set_data(const UniformType& data, BufferUsage usage) {
		Buffer::set_data<UniformType>(data, usage);
	}

	void set_data(const UniformType& data) {
		Buffer::set_sub_data<UniformType>(0, data);
	}

	template <typename T>
	void set_sub_data(unsigned int offset, const T& data) {
		Buffer::set_sub_data<T>(offset, data);
	}
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFERS_UNIFORM_BUFFER_HPP
