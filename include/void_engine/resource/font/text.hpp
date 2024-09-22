#ifndef VOID_ENGINE_RESOURCE_FONT_TEXT_HPP
#define VOID_ENGINE_RESOURCE_FONT_TEXT_HPP

#include "void_engine/graphics/mesh.hpp"
#include "void_engine/resource/font/font.hpp"

#include <glm/ext/vector_float2.hpp>
#include <string>
#include <string_view>

namespace void_engine::resource::font {

class Text {
public:
	Text(const Text& other);
	Text(Text&& other) noexcept;
	auto operator=(const Text& other) -> Text&;
	auto operator=(Text&& other) noexcept -> Text&;
	explicit Text(const Font& font, std::string_view data);
	~Text();

	void set_font(Font& font);
	void set_data(std::string_view data);

	[[nodiscard]] auto get_font() const -> const Font&;
	[[nodiscard]] auto get_data() const -> const std::string&;
	[[nodiscard]] auto get_size() const -> const glm::vec2&;
	[[nodiscard]] auto get_mesh() const -> const graphics::Mesh&;

private:
	const Font* _font;
	std::string _data;
	mutable glm::vec2 _size = {0.0f, 0.0f};
	mutable graphics::Mesh* _mesh = nullptr;
	mutable bool _dirty = false;

	void update() const;
};

} // namespace void_engine::resource::font

#endif // VOID_ENGINE_RESOURCE_FONT_TEXT_HPP
