#ifndef VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_HPP
#define VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_HPP

#include "void_engine/renderer/buffer/element_buffer.hpp"
#include "void_engine/renderer/buffer/vertex_buffer.hpp"
#include "void_engine/renderer/vertex_array/vertex_array_layout.hpp"

namespace void_engine::renderer::vertex_array {

class VertexArray {
public:
	VertexArray(const VertexArray& other);
	VertexArray(VertexArray&& other) noexcept;
	auto operator=(const VertexArray& other) -> VertexArray&;
	auto operator=(VertexArray&& other) noexcept -> VertexArray&;
	VertexArray();
	explicit VertexArray(const VertexArrayLayout& layout);
	VertexArray(
		const VertexArrayLayout& layout, const buffer::VertexBuffer& vertex_buffer,
		const buffer::ElementBuffer& element_buffer
	);
	~VertexArray();

	void bind() const;
	static void unbind();

	void add_vertex_buffer(
		const buffer::VertexBuffer& buffer, unsigned int index, unsigned int offset,
		unsigned int stride
	) const;
	void set_vertex_buffer(const buffer::VertexBuffer& buffer) const;
	void set_element_buffer(const buffer::ElementBuffer& buffer) const;

	void add_attribute(
		unsigned int index, unsigned int count, unsigned int offset, unsigned int type,
		bool normalized
	) const;

	void set_layout(const VertexArrayLayout& layout) const;

private:
	unsigned int _id{};
};

} // namespace void_engine::renderer::vertex_array

#endif // !VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_HPP
