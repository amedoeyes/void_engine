#ifndef VOID_ENGINE_GRAPHICS_BUFFER_ELEMENT_BUFFER_HPP
#define VOID_ENGINE_GRAPHICS_BUFFER_ELEMENT_BUFFER_HPP

#include "void_engine/graphics/buffer/buffer.hpp"
#include "void_engine/graphics/buffer/enums.hpp"

#include <vector>

namespace void_engine::graphics::buffer {

class ElementBuffer final : public Buffer {
public:
	ElementBuffer();
	explicit ElementBuffer(unsigned int size, Usage usage = Usage::static_draw);
	explicit ElementBuffer(
		const std::vector<unsigned int>& indices, Usage usage = Usage::static_draw
	);

	void set_data(const std::vector<unsigned int>& indices, Usage usage = Usage::static_draw);
	void update_data(const std::vector<unsigned int>& indices);

	[[nodiscard]] auto get_count() const -> unsigned int;

private:
	unsigned int _count = 0;
};

} // namespace void_engine::graphics::buffer

#endif // !VOID_ENGINE_GRAPHICS_BUFFER_ELEMENT_BUFFER_HPP
