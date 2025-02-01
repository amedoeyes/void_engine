export module void_engine.graphics:text;

import :mesh;
import :font_atlas;

import std;
import glm;

export namespace void_engine::graphics {

class Text {
public:
	explicit Text(FontAtlas& atlas, std::string_view data = "");

	void set_atlas(FontAtlas& atlas);
	void set_data(std::string_view data);

	[[nodiscard]]
	auto get_atlas() const -> FontAtlas&;
	[[nodiscard]]
	auto get_data() const -> const std::string&;
	[[nodiscard]]
	auto get_size() const -> const glm::vec2&;
	[[nodiscard]]
	auto get_mesh() const -> const Mesh&;

private:
	std::reference_wrapper<FontAtlas> _atlas;
	std::string _data;
	mutable glm::vec2 _size = {0.0f, 0.0f};
	mutable Mesh _mesh;
	mutable bool _dirty = false;

	void update() const;
};

} // namespace void_engine::graphics
