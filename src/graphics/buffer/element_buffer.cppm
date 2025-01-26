export module void_engine.graphics:buffer.element;

import :buffer;
import :buffer.enums;

import std;

export namespace void_engine::graphics::buffer {

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
