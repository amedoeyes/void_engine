export module void_engine.graphics:vertex_array;

import :buffer;
import :buffer.array;
import :buffer.element;

import void_engine.utility.get_gl_type;

export namespace void_engine::graphics {

class VertexArray {
public:
	VertexArray(const VertexArray& other);
	VertexArray(VertexArray&& other) noexcept;
	auto operator=(const VertexArray& other) -> VertexArray&;
	auto operator=(VertexArray&& other) noexcept -> VertexArray&;
	VertexArray();
	~VertexArray();

	void bind() const;
	static void unbind();

	template<typename T>
	void add_attribute(unsigned int count, unsigned int offset = 0, bool normalized = false) {
		add_attribute(utility::get_gl_type<T>(), count, offset, normalized);
	}

	template<typename T>
	void add_vertex_buffer(const buffer::ArrayBuffer<T>& buffer) {
		add_vertex_buffer(buffer, 0, sizeof(T));
	}

	void set_divisor(unsigned int divisor) const;
	void set_element_buffer(const buffer::ElementBuffer& buffer) const;

private:
	unsigned int _id = 0;
	unsigned int _index = 0;
	unsigned int _buffer_index = 0;

	void add_attribute(unsigned int type, unsigned int count, unsigned int offset, bool normalized);
	void add_vertex_buffer(const buffer::Buffer& buffer, unsigned int offset, unsigned int stride);
};

} // namespace void_engine::graphics
