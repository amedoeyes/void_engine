#include "void_engine/resources/image.hpp"

#include <csetjmp>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <png.h>
#include <vector>

namespace void_engine::resources {

namespace {

void close_file(FILE* fp) {
	if (fclose(fp) != 0) {
		perror("fclose");
	}
}

} // namespace

auto read_image(const std::filesystem::path& path, bool flip) -> Image* {
	FILE* fp = fopen(path.c_str(), "rb");
	if (fp == nullptr) {
		return nullptr;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png_ptr == nullptr) {
		close_file(fp);
		return nullptr;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) {
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		close_file(fp);
		return nullptr;
	}

	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);

	unsigned int width = 0;
	unsigned int height = 0;
	int bit_depth = 0;
	int color_type = 0;

	png_get_IHDR(
		png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr
	);
	auto* image = new Image;
	image->width = width;
	image->height = height;
	image->bit_depth = bit_depth;
	image->color_type = static_cast<ImageColorType>(color_type);

	const size_t row_size = png_get_rowbytes(png_ptr, info_ptr);
	std::vector<unsigned char*> row_bytes(image->height);
	image->bytes.resize(row_size * height);
	unsigned char* bytes = image->bytes.data();
	if (flip) {
		for (size_t i = 0; i < height; ++i) {
			row_bytes[height - i - 1] = bytes + i * row_size;
		}
	} else {
		for (size_t i = 0; i < height; ++i) {
			row_bytes[i] = bytes + i * row_size;
		}
	}
	png_read_image(png_ptr, row_bytes.data());

	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	close_file(fp);
	return image;
}

void write_image(const std::filesystem::path& path, Image* image) {
	FILE* fp = fopen(path.c_str(), "wb");
	if (fp == nullptr) {
		return;
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png_ptr == nullptr) {
		close_file(fp);
		return;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) {
		png_destroy_write_struct(&png_ptr, nullptr);
		close_file(fp);
		return;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(
		png_ptr,
		info_ptr,
		image->width,
		image->height,
		static_cast<int>(image->bit_depth),
		static_cast<int>(image->color_type),
		0,
		0,
		0
	);

	std::vector<unsigned char*> row_pointers(image->height);
	const size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	unsigned char* bytes = image->bytes.data();
	for (size_t i = 0; i < image->height; ++i) {
		row_pointers[i] = bytes + i * rowbytes;
	}

	png_write_info(png_ptr, info_ptr);
	png_write_image(png_ptr, row_pointers.data());

	png_destroy_write_struct(&png_ptr, &info_ptr);
	close_file(fp);
}

} // namespace void_engine::resources
