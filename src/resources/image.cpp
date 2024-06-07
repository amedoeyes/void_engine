#include "void_engine/resources/image.hpp"

#include "png.h"
#include "pngconf.h"

#include <csetjmp>
#include <cstddef>
#include <cstdio>
#include <string_view>
#include <vector>

namespace void_engine::resources {

auto read_image(std::string_view filename, bool flip) -> Image* {
	FILE* fp = fopen(filename.data(), "rb");
	if (fp == nullptr) {
		return nullptr;
	}

	png_structp png_ptr = png_create_read_struct(
		PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr
	);
	if (png_ptr == nullptr) {
		fclose(fp);
		return nullptr;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) {
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		fclose(fp);
		return nullptr;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		fclose(fp);
		return nullptr;
	}

	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);

	auto* image = new Image;
	png_get_IHDR(
		png_ptr, info_ptr, &image->width, &image->height, &image->bit_depth,
		reinterpret_cast<int*>(&image->color_type),
		reinterpret_cast<int*>(&image->interlace_type),
		reinterpret_cast<int*>(&image->compression_type),
		reinterpret_cast<int*>(&image->filter_method)
	);

	image->bytes.resize(png_get_rowbytes(png_ptr, info_ptr) * image->height);
	std::vector<png_bytep> row_pointers(image->height);
	if (flip) {
		for (size_t i = image->height; i > 0; --i) {
			row_pointers[image->height - i] = reinterpret_cast<png_bytep>(
				image->bytes.data() +
				(i - 1) * png_get_rowbytes(png_ptr, info_ptr)
			);
		}
	} else {
		for (size_t i = 0; i < image->height; ++i) {
			row_pointers[i] = reinterpret_cast<png_bytep>(
				image->bytes.data() + i * png_get_rowbytes(png_ptr, info_ptr)
			);
		}
	}

	png_read_image(png_ptr, row_pointers.data());

	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	fclose(fp);

	return image;
}

void write_image(std::string_view filename, const Image* image) {
	FILE* fp = fopen(filename.data(), "wb");
	if (fp == nullptr) {
		return;
	}

	png_structp png_ptr = png_create_write_struct(
		PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr
	);
	if (png_ptr == nullptr) {
		fclose(fp);
		return;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) {
		png_destroy_write_struct(&png_ptr, nullptr);
		fclose(fp);
		return;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(
		png_ptr, info_ptr, image->width, image->height, image->bit_depth,
		static_cast<int>(image->color_type),
		static_cast<int>(image->interlace_type),
		static_cast<int>(image->compression_type),
		static_cast<int>(image->filter_method)
	);

	std::vector<png_bytep> row_pointers(image->height);
	const size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	for (size_t i = 0; i < image->height; ++i) {
		row_pointers[i] = reinterpret_cast<png_bytep>(
			const_cast<std::byte*>(&image->bytes[i * rowbytes])
		);
	}

	png_write_info(png_ptr, info_ptr);
	png_write_image(png_ptr, row_pointers.data());

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
}

} // namespace void_engine::resources
