#ifndef VOID_ENGINE_RESOURCES_IMAGE_HPP
#define VOID_ENGINE_RESOURCES_IMAGE_HPP

#include <cstddef>
#include <png.h>
#include <string_view>
#include <vector>

namespace void_engine::resources {

enum class ImageColorType {
	gray = PNG_COLOR_TYPE_GRAY,
	gray_alpha = PNG_COLOR_TYPE_GRAY_ALPHA,
	rgb = PNG_COLOR_TYPE_RGB,
	rgba = PNG_COLOR_TYPE_RGBA,
	palette = PNG_COLOR_TYPE_PALETTE,
};

enum class ImageInterlaceType {
	none = PNG_INTERLACE_NONE,
	adam7 = PNG_INTERLACE_ADAM7,
};

enum class ImageCompressionType {
	base = PNG_COMPRESSION_TYPE_BASE,
};

enum class ImageFilterMethod {
	base = PNG_FILTER_TYPE_BASE,
};

struct Image {
	unsigned int width;
	unsigned int height;
	int bit_depth;
	ImageColorType color_type;
	ImageInterlaceType interlace_type;
	ImageCompressionType compression_type;
	ImageFilterMethod filter_method;
	std::vector<std::byte> bytes;
};

auto read_image(std::string_view filename, bool flip = false) -> Image*;
void write_image(std::string_view filename, const Image* image);

} // namespace void_engine::resources

#endif // !#ifndef VOID_ENGINE_RESOURCES_IMAGE_HPP
