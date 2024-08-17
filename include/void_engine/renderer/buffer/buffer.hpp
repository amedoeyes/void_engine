#ifndef VOID_ENGINE_RENDERER_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_HPP

#include <cstdint>

namespace void_engine::renderer::buffer {

enum class BufferTarget : uint16_t {
	array = 0x8892,
	atomic_counter = 0x92C0,
	copy_read = 0x8F36,
	copy_write = 0x8F37,
	dispatch_indirect = 0x90EE,
	draw_indirect = 0x8F3F,
	element_array = 0x8893,
	pixel_pack = 0x88EB,
	pixel_unpack = 0x88EC,
	query = 0x9192,
	shader_storage = 0x90D2,
	texture = 0x8C2A,
	transform_feedback = 0x8C8E,
	uniform = 0x8A11
};

enum class BufferUsage : uint16_t {
	stream_draw = 0x88E0,
	stream_read = 0x88E1,
	stream_copy = 0x88E2,
	static_draw = 0x88E4,
	static_read = 0x88E5,
	static_copy = 0x88E6,
	dynamic_draw = 0x88E8,
	dynamic_read = 0x88E9,
	dynamic_copy = 0x88EA
};

class Buffer {
public:
	Buffer(const Buffer& other);
	Buffer(Buffer&& other) noexcept;
	auto operator=(const Buffer& other) -> Buffer&;
	auto operator=(Buffer&& other) noexcept -> Buffer&;
	explicit Buffer(BufferTarget target);
	~Buffer();

	void bind() const;
	void unbind() const;

	void allocate(unsigned int size, BufferUsage usage);
	void set_data(unsigned int size, const void* data, BufferUsage usage);
	void set_sub_data(unsigned int offset, unsigned int size, const void* data) const;
	void update_data(const void* data) const;

	template <typename T>
	void set_data(const T& data, BufferUsage usage) {
		set_data(sizeof(T), &data, usage);
	}

	template <typename T>
	void set_sub_data(unsigned int offset, const T& data) const {
		set_sub_data(offset, sizeof(T), &data);
	}

	void bind_range(unsigned int index, unsigned int offset, unsigned int size) const;

	[[nodiscard]] auto get_id() const -> unsigned int;

private:
	unsigned int _id = 0;
	BufferTarget _target;
	unsigned int _allocated_size = 0;
};

} // namespace void_engine::renderer::buffer

#endif // !VOID_ENGINE_RENDERER_BUFFER_HPP
