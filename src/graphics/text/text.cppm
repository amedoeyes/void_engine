export module void_engine.graphics:text;

import :mesh;

import std;
import glm;
import void_engine.resources;

export namespace void_engine::graphics {

class Text {
public:
	Text(const Text& other);
	Text(Text&& other) noexcept;
	auto operator=(const Text& other) -> Text&;
	auto operator=(Text&& other) noexcept -> Text&;
	Text() = default;
	explicit Text(const resources::Font& font, std::string_view data);
	~Text();

	void set_font(const resources::Font& font);
	void set_data(std::string_view data);

	[[nodiscard]] auto get_font() const -> const resources::Font&;
	[[nodiscard]] auto get_data() const -> const std::string&;
	[[nodiscard]] auto get_size() const -> const glm::vec2&;
	[[nodiscard]] auto get_mesh() const -> const Mesh&;

private:
	const resources::Font* _font = nullptr;
	std::string _data;
	mutable glm::vec2 _size = {0.0f, 0.0f};
	mutable Mesh* _mesh = nullptr;
	mutable bool _dirty = false;

	void update() const;
};

} // namespace void_engine::graphics
