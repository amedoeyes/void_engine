#ifndef VOID_ENGINE_UTILITY_IMAGE_HPP
#define VOID_ENGINE_UTILITY_IMAGE_HPP

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <glm/ext/vector_uint2.hpp>
#include <span>
#include <vector>

namespace void_engine::utility {

enum class ImageColorType : uint8_t {
	none,
	gray,
	gray_alpha,
	rgb,
	rgba,
};

class Image {
public:
	Image(const Image&) = default;
	Image(Image&&) = default;
	auto operator=(const Image&) -> Image& = default;
	auto operator=(Image&&) -> Image& = default;
	Image(std::span<const std::byte> data, ImageColorType color_type, const glm::uvec2& size);
	explicit Image(const std::filesystem::path& path, bool flip = false);
	explicit Image(std::span<std::byte> data, bool flip = false);
	~Image() = default;

	void write(const std::filesystem::path& path) const;

	[[nodiscard]] auto get_data() const -> std::span<const std::byte>;
	[[nodiscard]] auto get_color_type() const -> ImageColorType;
	[[nodiscard]] auto get_size() const -> const glm::uvec2&;

private:
	std::vector<std::byte> _data;
	ImageColorType _color_type;
	glm::uvec2 _size = {0, 0};
};

} // namespace void_engine::utility

#endif // !VOID_ENGINE_UTILITY_IMAGE_HPP
