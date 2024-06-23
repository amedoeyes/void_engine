#ifndef VOID_ENGINE_RENDERER_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_HPP

namespace void_engine::renderer {

#include <glad/gl.h>

enum class BufferTarget {
	array = GL_ARRAY_BUFFER,
	atomic_counter = GL_ATOMIC_COUNTER_BUFFER,
	copy_read = GL_COPY_READ_BUFFER,
	copy_write = GL_COPY_WRITE_BUFFER,
	dispatch_indirect = GL_DISPATCH_INDIRECT_BUFFER,
	draw_indirect = GL_DRAW_INDIRECT_BUFFER,
	element_array = GL_ELEMENT_ARRAY_BUFFER,
	pixel_pack = GL_PIXEL_PACK_BUFFER,
	pixel_unpack = GL_PIXEL_UNPACK_BUFFER,
	query = GL_QUERY_BUFFER,
	shader_storage = GL_SHADER_STORAGE_BUFFER,
	texture = GL_TEXTURE_BUFFER,
	transform_feedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	uniform = GL_UNIFORM_BUFFER
};

enum class BufferUsage {
	stream_draw = GL_STREAM_DRAW,
	stream_read = GL_STREAM_READ,
	stream_copy = GL_STREAM_COPY,
	static_draw = GL_STATIC_DRAW,
	static_read = GL_STATIC_READ,
	static_copy = GL_STATIC_COPY,
	dynamic_draw = GL_DYNAMIC_DRAW,
	dynamic_read = GL_DYNAMIC_READ,
	dynamic_copy = GL_DYNAMIC_COPY
};

class Buffer {
public:
	Buffer(BufferTarget target);
	~Buffer();

public:
	void bind() const;
	void unbind() const;

	void set_data(unsigned int size, const void* data, BufferUsage usage);
	void set_sub_data(unsigned int offset, unsigned int size, const void* data);

	[[nodiscard]] auto get_id() const -> unsigned int;
	[[nodiscard]] auto get_count() const -> unsigned int;
	void set_count(unsigned int count);

private:
	unsigned int _id;
	unsigned int _target;
	unsigned int _count;
};

} // namespace void_engine::renderer

#endif // !VOID_ENGINE_RENDERER_BUFFER_HPP
