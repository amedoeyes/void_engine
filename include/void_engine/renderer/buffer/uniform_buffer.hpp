#ifndef VOID_ENGINE_RENDERER_BUFFER_UNIFORM_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_UNIFORM_BUFFER_HPP

#include "void_engine/renderer/buffer/buffer.hpp"

namespace void_engine::renderer::buffer {

template <typename UniformType>
class UniformBuffer final : public Buffer {
public:
	UniformBuffer(unsigned int index, const UniformType& data, BufferUsage usage) :
		Buffer(BufferTarget::uniform) {
		set_data(data, usage);
		Buffer::bind_range(index, 0, sizeof(UniformType));
	}

	void set_data(const UniformType& data, BufferUsage usage) {
		Buffer::set_data<UniformType>(data, usage);
	}

	void update_data(const UniformType& data) {
		Buffer::update_data(&data);
	}
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFER_UNIFORM_BUFFER_HPP
