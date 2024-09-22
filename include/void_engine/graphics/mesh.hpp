#ifndef VOID_ENGINE_GRAPHICS_MESH_HPP
#define VOID_ENGINE_GRAPHICS_MESH_HPP

#include "void_engine/graphics/buffer/array_buffer.hpp"
#include "void_engine/graphics/buffer/buffer.hpp"
#include "void_engine/graphics/buffer/element_buffer.hpp"
#include "void_engine/graphics/buffer/enums.hpp"
#include "void_engine/graphics/renderer/enums.hpp"
#include "void_engine/graphics/vertex_array.hpp"

#include <vector>

namespace void_engine::graphics {

class Mesh {
public:
	Mesh(const Mesh& other);
	Mesh(Mesh&& other) noexcept;
	auto operator=(const Mesh& other) -> Mesh&;
	auto operator=(Mesh&& other) noexcept -> Mesh&;
	Mesh();
	explicit Mesh(renderer::PrimitiveType primitive_type);
	~Mesh();

	void bind() const;
	static void unbind();

	template <typename T>
	void add_attribute(unsigned int count, unsigned int offset = 0, bool normalized = false) {
		_vertex_array->add_attribute<T>(count, offset, normalized);
	}

	template <typename T>
	void add_vertex_buffer(
		const std::vector<T>& data, buffer::Usage usage = buffer::Usage::static_draw
	) {
		auto* buffer = new buffer::ArrayBuffer(data, usage);
		_vertex_array->add_vertex_buffer(*buffer);
		_vertex_buffers.push_back(buffer);
	}

	void set_divisor(unsigned int divisor) const;
	void set_indices(
		const std::vector<unsigned int>& data, buffer::Usage usage = buffer::Usage::static_draw
	);
	void set_primitive_type(renderer::PrimitiveType primitive);

	[[nodiscard]] auto get_vertex_array() -> VertexArray&;
	[[nodiscard]] auto get_vertex_array() const -> const VertexArray&;
	[[nodiscard]] auto get_element_buffer() -> buffer::ElementBuffer&;
	[[nodiscard]] auto get_element_buffer() const -> const buffer::ElementBuffer&;
	[[nodiscard]] auto get_primitive_type() const -> renderer::PrimitiveType;
	[[nodiscard]] auto get_count() const -> unsigned int;

	template <typename T>
	[[nodiscard]] auto get_vertex_buffer(unsigned int index) -> buffer::ArrayBuffer<T>& {
		return *static_cast<buffer::ArrayBuffer<T>*>(_vertex_buffers[index]);
	}
	template <typename T>
	[[nodiscard]] auto get_vertex_buffer(unsigned int index) const -> const buffer::ArrayBuffer<T>& {
		return *static_cast<buffer::ArrayBuffer<T>*>(_vertex_buffers[index]);
	}

private:
	VertexArray* _vertex_array;
	std::vector<buffer::Buffer*> _vertex_buffers;
	buffer::ElementBuffer* _element_buffer;
	renderer::PrimitiveType _primitive_type;
};

} // namespace void_engine::graphics

#endif // !VOID_ENGINE_GRAPHICS_MESH_HPP
