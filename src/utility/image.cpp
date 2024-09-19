#include "void_engine/utility/image.hpp"

#include <cassert>
#include <glm/ext/vector_uint2.hpp>
#include <span>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <bit>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <stb_image.h>
#include <stb_image_write.h>
#include <vector>

namespace void_engine::utility {

Image::Image(std::span<const std::byte> data, ImageColorType color_type, const glm::uvec2& size) :
	_data(data.begin(), data.end()),
	_color_type(color_type),
	_size(size) {
}

Image::Image(const std::filesystem::path& path, bool flip) {
	int width = 0;
	int height = 0;
	int channels = 0;
	stbi_set_flip_vertically_on_load(static_cast<int>(flip));
	unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
	assert(data != nullptr && "Failed to load image");
	const unsigned int size = width * height * channels;
	_data.resize(size);
	std::memcpy(_data.data(), data, size);
	_size = {width, height};
	_color_type = static_cast<ImageColorType>(channels);
	stbi_image_free(data);
}

Image::Image(std::span<std::byte> data, bool flip) {
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
	assert(image_data != nullptr && "Failed to load image");
	const unsigned int size = width * height * channels;
	_data.resize(size);
	std::memcpy(_data.data(), image_data, size);
	_size = {width, height};
	_color_type = static_cast<ImageColorType>(channels);
	stbi_image_free(image_data);
}

void Image::write(const std::filesystem::path& path) const {
	const int result = stbi_write_png(
		path.string().c_str(),
		static_cast<int>(_size.x),
		static_cast<int>(_size.y),
		static_cast<int>(_color_type),
		_data.data(),
		0
	);
	if (result == 0) {
		assert(false && "Failed to write image");
	}
}

auto Image::get_data() const -> std::span<const std::byte> {
	return _data;
}

auto Image::get_color_type() const -> ImageColorType {
	return _color_type;
}

auto Image::get_size() const -> const glm::uvec2& {
	return _size;
}

} // namespace void_engine::utility
