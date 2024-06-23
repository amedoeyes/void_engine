#ifndef VOID_ENGINE_RENDERER_VERTEX_ARRAY_HPP
#define VOID_ENGINE_RENDERER_VERTEX_ARRAY_HPP

#include "buffer.hpp"

namespace void_engine::renderer {

class VertexArray {
public:
	VertexArray();
	~VertexArray();

public:
	void bind() const;
	void unbind() const;

	void
	set_vertex_buffer(unsigned int size, const void* data, BufferUsage usage);
	void add_buffer(int size, int stride, unsigned int offset);

private:
	unsigned int _id;
	Buffer _vertex_buffer;
	unsigned int _index = 0;
};

} // namespace void_engine::renderer

#endif // !VOID_ENGINE_RENDERER_VERTEX_ARRAY_HPP
