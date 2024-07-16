#ifndef VOID_ENGINE_RENDERER_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_HPP

namespace void_engine::renderer::buffers {

enum class BufferTarget {
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

enum class BufferUsage {
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
	Buffer(const Buffer&) = default;
	Buffer(Buffer&&) = delete;
	auto operator=(const Buffer&) -> Buffer& = default;
	auto operator=(Buffer&&) -> Buffer& = delete;
	explicit Buffer(BufferTarget target);
	~Buffer();

	void bind() const;
	void unbind() const;

	void set_data(unsigned int size, const void* data, BufferUsage usage) const;

	template <typename T>
	void set_data(const T& data, BufferUsage usage) {
		set_data(sizeof(T), &data, usage);
	}

	void set_sub_data(unsigned int offset, unsigned int size, const void* data) const;

	template <typename T>
	void set_sub_data(unsigned int offset, const T& data) {
		set_sub_data(offset, sizeof(T), &data);
	}

	void bind_buffer_range(unsigned int index, unsigned int offset, unsigned int size) const;

	[[nodiscard]] auto get_id() const -> unsigned int;

private:
	unsigned int _id = 0;
	unsigned int _target;
};

} // namespace void_engine::renderer::buffers

#endif // !VOID_ENGINE_RENDERER_BUFFER_HPP
