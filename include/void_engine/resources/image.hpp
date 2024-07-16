#ifndef VOID_ENGINE_RESOURCES_IMAGE_HPP
#define VOID_ENGINE_RESOURCES_IMAGE_HPP

#include <cstdint>
#include <filesystem>
#include <vector>

namespace void_engine::resources {

enum class ImageColorType : uint8_t {
	gray = 0,
	gray_alpha = 4,
	rgb = 2,
	rgba = 6,
	palette = 3,
};

struct Image {
	unsigned int width;
	unsigned int height;
	unsigned int bit_depth;
	ImageColorType color_type;
	std::vector<unsigned char> bytes;
};

auto read_image(const std::filesystem::path& path, bool flip = false) -> Image*;
void write_image(const std::filesystem::path& path, Image* image);

} // namespace void_engine::resources

#endif // !VOID_ENGINE_RESOURCES_IMAGE_HPP
