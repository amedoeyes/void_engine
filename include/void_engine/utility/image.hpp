#ifndef VOID_ENGINE_UTILITY_IMAGE_HPP
#define VOID_ENGINE_UTILITY_IMAGE_HPP

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <glm/ext/vector_int2.hpp>
#include <optional>
#include <vector>

namespace void_engine::utility {

enum class ImageColorType : uint8_t {
	gray = 1,
	gray_alpha,
	rgb,
	rgba,
};

struct Image {
	glm::ivec2 size;
	ImageColorType color_type;
	std::vector<std::byte> data;
};

auto read_image(const std::filesystem::path& path, bool flip = false) -> std::optional<Image>;
auto read_image(const std::vector<std::byte>& data, bool flip = false) -> std::optional<Image>;
auto write_image(const std::filesystem::path& path, const Image& image) -> bool;

} // namespace void_engine::utility

#endif // !VOID_ENGINE_UTILITY_IMAGE_HPP
