#include "void_engine/utility/image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <bit>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <optional>
#include <stb_image.h>
#include <stb_image_write.h>
#include <vector>

namespace void_engine::utility {

auto read_image(const std::filesystem::path& path, bool flip) -> std::optional<Image> {
	int width = 0;
	int height = 0;
	int channels = 0;
	stbi_set_flip_vertically_on_load(static_cast<int>(flip));
	unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
	if (data == nullptr) {
		return std::nullopt;
	}
	const unsigned int size = width * height * channels;
	Image image;
	image.size = {width, height};
	image.color_type = static_cast<ImageColorType>(channels);
	image.data.resize(size);
	std::memcpy(image.data.data(), data, size);
	stbi_image_free(data);
	return image;
}

auto read_image(const std::vector<std::byte>& data, bool flip) -> std::optional<Image> {
	int width = 0;
	int height = 0;
	int channels = 0;
	stbi_set_flip_vertically_on_load(static_cast<int>(flip));
	// NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
	unsigned char* image_data = stbi_load_from_memory(
		std::bit_cast<const unsigned char*>(data.data()),
		static_cast<int>(data.size()),
		&width,
		&height,
		&channels,
		0
	);
	if (image_data == nullptr) {
		return std::nullopt;
	}
	const unsigned int size = width * height * channels;
	Image image;
	image.size = {width, height};
	image.color_type = static_cast<ImageColorType>(channels);
	image.data.resize(size);
	std::memcpy(image.data.data(), image_data, size);
	stbi_image_free(image_data);
	return image;
}

auto write_image(const std::filesystem::path& path, const Image& image) -> bool {
	const int result = stbi_write_png(
		path.string().c_str(),
		image.size.x,
		image.size.y,
		static_cast<int>(image.color_type),
		image.data.data(),
		0
	);
	return result != 0;
}

} // namespace void_engine::utility
