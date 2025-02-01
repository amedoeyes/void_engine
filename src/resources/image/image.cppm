export module void_engine.resources:image;

import :image_enums;

import std;
import glm;

export namespace void_engine::resources {

class Image {
public:
	Image(const Image&) = default;
	Image(Image&&) = default;
	auto operator=(const Image&) -> Image& = default;
	auto operator=(Image&&) -> Image& = default;
	Image(std::span<const std::byte> data, ColorType color_type, const glm::uvec2& size);
	explicit Image(const std::filesystem::path& path, bool flip = false);
	explicit Image(std::span<std::byte> data, bool flip = false);
	~Image() = default;

	void write(const std::filesystem::path& path) const;

	[[nodiscard]]
	auto get_data() const -> std::span<const std::byte>;
	[[nodiscard]]
	auto get_color_type() const -> ColorType;
	[[nodiscard]]
	auto get_size() const -> const glm::ivec2&;

private:
	std::vector<std::byte> _data;
	ColorType _color_type;
	glm::ivec2 _size = {0, 0};
};

} // namespace void_engine::resources
