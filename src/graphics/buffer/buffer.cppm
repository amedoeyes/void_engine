export module void_engine.graphics:buffer;

import :buffer.enums;

export namespace void_engine::graphics::buffer {

class Buffer {
public:
	Buffer(const Buffer& other);
	Buffer(Buffer&& other) noexcept;
	auto operator=(const Buffer& other) -> Buffer&;
	auto operator=(Buffer&& other) noexcept -> Buffer&;
	explicit Buffer(Target target);
	virtual ~Buffer();

	void bind() const;
	void unbind() const;

	void allocate(unsigned int size, Usage usage);
	void set_data(unsigned int size, const void* data, Usage usage);
	void set_sub_data(unsigned int offset, unsigned int size, const void* data) const;
	void update_data(const void* data) const;
	void bind_range(unsigned int index, unsigned int offset, unsigned int size) const;

	template <typename T>
	void set_data(const T& data, Usage usage) {
		set_data(sizeof(T), &data, usage);
	}

	template <typename T>
	void set_sub_data(unsigned int offset, const T& data) const {
		set_sub_data(offset, sizeof(T), &data);
	}

	template <typename T>
	void update_data(const T& data) const {
		update_data(static_cast<const void*>(&data));
	}

	template <typename T>
	void bind_range(unsigned int index, unsigned int offset) const {
		bind_range(index, offset, sizeof(T));
	}

	[[nodiscard]] auto get_id() const -> unsigned int;

protected:
	unsigned int _id = 0;
	Target _target = Target::none;
	Usage _usage = Usage::none;
	unsigned int _allocated_size = 0;
};

} // namespace void_engine::graphics::buffer
