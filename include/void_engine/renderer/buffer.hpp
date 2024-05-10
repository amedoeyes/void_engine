#ifndef VOID_ENGINE_RENDERER_BUFFER_HPP
#define VOID_ENGINE_RENDERER_BUFFER_HPP

#include <glad/gl.h>

#include "common.hpp"

namespace void_engine::renderer {

class Buffer {
	public:
	public:
	Buffer(BufferTarget target);
	~Buffer();

	public:
	void bind() const;
	void unbind() const;

	void set_data(unsigned int size, const void* data, BufferUsage usage);
	void set_sub_data(unsigned int offset, unsigned int size, const void* data);

	unsigned int get_id() const;
	unsigned int get_count() const;
	void set_count(unsigned int count);

	private:
	unsigned int _id;
	unsigned int _target;
	unsigned int _count;
};

}  // namespace void_engine::renderer

#endif	// !VOID_ENGINE_RENDERER_BUFFER_HPP
