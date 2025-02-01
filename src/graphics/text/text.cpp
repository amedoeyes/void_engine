module;

#include <cassert>

module void_engine.graphics;

import std;
import glm;

namespace void_engine::graphics {

Text::Text(FontAtlas& atlas, std::string_view data) : _atlas(atlas), _data(data) {
	_mesh.add_attribute<float>(2);
	_mesh.add_vertex_buffer<glm::vec2>({}, buffer::Usage::dynamic_draw);
	_mesh.add_attribute<float>(2);
	_mesh.add_vertex_buffer<glm::vec2>({}, buffer::Usage::dynamic_draw);
	update();
}

void Text::set_atlas(FontAtlas& atlas) {
	_atlas = atlas;
	_dirty = true;
}

void Text::set_data(std::string_view data) {
	if (_data == data) {
		return;
	}
	_data = data;
	_dirty = true;
}

auto Text::get_atlas() const -> FontAtlas& { return _atlas.get(); }

auto Text::get_data() const -> const std::string& { return _data; }

auto Text::get_size() const -> const glm::vec2& {
	if (_dirty) {
		update();
		_dirty = false;
	}
	return _size;
}

auto Text::get_mesh() const -> const Mesh& {
	if (_dirty) {
		update();
		_dirty = false;
	}
	return _mesh;
}

void Text::update() const {
	const auto glyphs = _atlas.get().glyphs(_data);
	auto positions = std::vector<glm::vec2>();
	positions.reserve(glyphs.size() * 4);
	auto uvs = std::vector<glm::vec2>();
	uvs.reserve(glyphs.size() * 4);
	auto indices = std::vector<unsigned int>();
	indices.reserve(glyphs.size() * 6);
	auto position_offset = glm::vec2(0.0f, 0.0f);
	auto indices_offset = 0;
	_size = {0.0f, 0.0f};
	for (const auto& [glyph, bitmap, uv] : glyphs) {
		const auto position = glm::vec2{
			position_offset.x + static_cast<float>(bitmap.bearing.x),
			position_offset.y - (static_cast<float>(bitmap.size.y) - static_cast<float>(bitmap.bearing.y)),
		};
		const auto size = glm::vec2(bitmap.size);
		const auto new_positions = std::array{
			glm::vec2(position.x, position.y + size.y),
			position,
			glm::vec2(position.x + size.x, position.y),
			position + size,
		};
		const auto new_uvs = std::array{
			uv.position,
			glm::vec2(uv.position.x, uv.position.y + uv.size.y),
			uv.position + uv.size,
			glm::vec2(uv.position.x + uv.size.x, uv.position.y),
		};
		const auto new_indices = std::array{
			indices_offset + 0,
			indices_offset + 1,
			indices_offset + 2,
			indices_offset + 0,
			indices_offset + 2,
			indices_offset + 3,
		};
		std::ranges::move(new_positions, std::back_inserter(positions));
		std::ranges::move(new_uvs, std::back_inserter(uvs));
		std::ranges::move(new_indices, std::back_inserter(indices));
		position_offset += glyph.advance;
		indices_offset += 4;
		_size = position + size;
	}
	_mesh.get_vertex_buffer<glm::vec2>(0).update_data(positions);
	_mesh.get_vertex_buffer<glm::vec2>(1).update_data(uvs);
	_mesh.set_indices(indices);
}

} // namespace void_engine::graphics
