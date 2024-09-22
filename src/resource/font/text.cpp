#include "void_engine/resource/font/text.hpp"

#include "void_engine/graphics/buffer/buffer.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/resource/font/font.hpp"
#include "void_engine/resource/font/glyph.hpp"

#include <algorithm>
#include <array>
#include <codecvt>
#include <glm/ext/vector_float2.hpp>
#include <iterator>
#include <locale>
#include <string_view>
#include <utility>
#include <vector>

namespace void_engine::resource::font {

Text::Text(const Text& other) : _font(other._font), _data(other._data) {
	update();
}

Text::Text(Text&& other) noexcept : _font(other._font), _data(std::move(other._data)) {
	other._mesh = nullptr;
	other._font = nullptr;
}

auto Text::operator=(const Text& other) -> Text& {
	if (this != &other) {
		_font = other._font;
		_data = other._data;
		update();
	}
	return *this;
}

auto Text::operator=(Text&& other) noexcept -> Text& {
	if (this != &other) {
		_font = other._font;
		_data = std::move(other._data);
		_mesh = other._mesh;
		other._mesh = nullptr;
		other._font = nullptr;
	}
	return *this;
}

Text::Text(const Font& font, std::string_view data) : _font(&font), _data(data) {
	update();
}

Text::~Text() {
	delete _mesh;
}

void Text::set_font(Font& font) {
	_font = &font;
	_dirty = true;
}

void Text::set_data(std::string_view data) {
	if (_data == data) {
		return;
	}
	_data = data;
	_dirty = true;
}

auto Text::get_font() const -> const Font& {
	return *_font;
}

auto Text::get_data() const -> const std::string& {
	return _data;
}

auto Text::get_size() const -> const glm::vec2& {
	if (_dirty) {
		update();
		_dirty = false;
	}
	return _size;
}
auto Text::get_mesh() const -> const graphics::Mesh& {
	if (_dirty) {
		update();
		_dirty = false;
	}
	return *_mesh;
}

void Text::update() const {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	const std::vector<Glyph> glyphs = _font->get_glyphs(converter.from_bytes(_data));
	std::vector<glm::vec2> positions;
	positions.reserve(glyphs.size() * 4);
	std::vector<glm::vec2> uvs;
	uvs.reserve(glyphs.size() * 4);
	std::vector<unsigned int> indices;
	indices.reserve(glyphs.size() * 6);
	glm::vec2 position_offset = {0.0f, 0.0f};
	unsigned int indices_offset = 0;
	_size = {0.0f, 0.0f};
	for (const auto& glyph : glyphs) {
		const glm::vec2 position = {
			position_offset.x + static_cast<float>(glyph.bearing.x),
			position_offset.y - (static_cast<float>(glyph.size.y) - static_cast<float>(glyph.bearing.y)),
		};
		const glm::vec2 size = glyph.size;
		const glm::vec2& uv_position = glyph.uv_position;
		const glm::vec2& uv_size = glyph.uv_size;
		const std::array<glm::vec2, 4> new_positions = {
			glm::vec2(position.x, position.y + size.y),
			position,
			glm::vec2(position.x + size.x, position.y),
			position + size,
		};
		const std::array<glm::vec2, 4> new_uvs = {
			uv_position,
			glm::vec2(uv_position.x, uv_position.y + uv_size.y),
			uv_position + uv_size,
			glm::vec2(uv_position.x + uv_size.x, uv_position.y),
		};
		const std::array<unsigned int, 6> new_indices = {
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
	if (_mesh == nullptr) {
		_mesh = new graphics::Mesh();
		_mesh->add_attribute<float>(2);
		_mesh->add_vertex_buffer(positions, graphics::buffer::BufferUsage::dynamic_draw);
		_mesh->add_attribute<float>(2);
		_mesh->add_vertex_buffer(uvs, graphics::buffer::BufferUsage::dynamic_draw);
	} else {
		_mesh->get_vertex_buffer<glm::vec2>(0).update_data(positions);
		_mesh->get_vertex_buffer<glm::vec2>(1).update_data(uvs);
	}
	_mesh->set_indices(indices);
}

} // namespace void_engine::resource::font
