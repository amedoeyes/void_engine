module void_engine.graphics;

import :buffer;
import :buffer.element;
import :buffer.enums;

import std;

namespace void_engine::graphics::buffer {

ElementBuffer::ElementBuffer() : Buffer(Target::element_array) {
}

ElementBuffer::ElementBuffer(unsigned int size, Usage usage) : ElementBuffer() {
	Buffer::allocate(size, usage);
}

ElementBuffer::ElementBuffer(const std::vector<unsigned int>& indices, Usage usage) :
	ElementBuffer() {
	set_data(indices, usage);
}

void ElementBuffer::set_data(const std::vector<unsigned int>& indices, Usage usage) {
	Buffer::set_data(indices.size() * sizeof(unsigned int), indices.data(), usage);
	_count = indices.size();
}

void ElementBuffer::update_data(const std::vector<unsigned int>& indices) {
	Buffer::update_data(indices.data());
	_count = indices.size();
}

auto ElementBuffer::get_count() const -> unsigned int {
	return _count;
}

} // namespace void_engine::graphics::buffer
