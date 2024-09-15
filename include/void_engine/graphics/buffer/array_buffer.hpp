#ifndef VOID_ENGINE_GRAPHICS_BUFFER_ARRAY_BUFFER_HPP
#define VOID_ENGINE_GRAPHICS_BUFFER_ARRAY_BUFFER_HPP

#include "void_engine/graphics/buffer/buffer.hpp"
#include "void_engine/utility/logger.hpp"

#include <vector>

namespace void_engine::graphics::buffer {

template <typename T>
class ArrayBuffer final : public Buffer {
public:
	ArrayBuffer() : Buffer(BufferTarget::array) {
	}
	explicit ArrayBuffer(unsigned int size, BufferUsage usage = BufferUsage::static_draw) :
		ArrayBuffer() {
		Buffer::allocate(size, usage);
	}
	explicit ArrayBuffer(const std::vector<T>& data, BufferUsage usage = BufferUsage::static_draw) :
		ArrayBuffer() {
		set_data(data, usage);
	}

	void set_data(const std::vector<T>& data, BufferUsage usage = BufferUsage::static_draw) {
		Buffer::set_data(data.size() * sizeof(T), data.data(), usage);
		_data = data;
	}

	void set_sub_data(unsigned int offset, const std::vector<T>& data) {
		Buffer::set_sub_data(offset, data.size() * sizeof(T), data.data());
		std::copy(data.begin(), data.end(), _data.begin() + offset);
	}

	void update_data(const std::vector<T>& data) {
		if (_data.size() < data.size()) {
			set_data(data, _usage);
		} else {
			Buffer::set_sub_data(0, data.size() * sizeof(T), data.data());
		}
		_data = data;
	}

	[[nodiscard]] auto get_data() const -> const std::vector<T>& {
		return _data;
	}

private:
	std::vector<T> _data;
};

} // namespace void_engine::graphics::buffer

#endif // !VOID_ENGINE_GRAPHICS_BUFFER_ARRAY_BUFFER_HPP
