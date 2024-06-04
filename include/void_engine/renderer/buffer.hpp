#ifndef VOID_ENGINE_RENDERER_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_HPP

#include "common.hpp"

#include <glad/gl.h>

namespace void_engine::renderer {

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
