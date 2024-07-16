#include "void_engine/resources/image.hpp"

#include "void_engine/utils/get_exec_path.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <filesystem>

using namespace void_engine::resources;
using namespace void_engine::utils;

TEST_CASE("Image", "[resources][image]") {
	const std::filesystem::path image_path =
		get_exec_path().parent_path() / "../../../../tests/resources/cat.png";

	SECTION("Read non-existent image") {
		const Image* image = read_image("non-existent.png");
		REQUIRE(image == nullptr);
		delete image;
	}

	SECTION("Read image") {
		const Image* image = read_image(image_path.string());
		REQUIRE(image != nullptr);
		REQUIRE(image->width == 1024);
		REQUIRE(image->height == 933);
		REQUIRE(image->bit_depth == 8);
		REQUIRE(image->color_type == ImageColorType::rgb);
		REQUIRE(image->bytes.size() == static_cast<size_t>(1024 * 933 * 3));
		delete image;
	}

	SECTION("Read image with flip") {
		const Image* image = read_image(image_path.string());
		const Image* image_flip = read_image(image_path.string(), true);
		REQUIRE(image != nullptr);
		REQUIRE(image_flip != nullptr);
		REQUIRE(image->bytes != image_flip->bytes);
		delete image;
		delete image_flip;
	}

	SECTION("Write image") {
		Image* image = read_image(image_path.string());
		REQUIRE(image != nullptr);
		write_image("cat_copy.png", image);
		const Image* image_copy = read_image("cat_copy.png");
		REQUIRE(image_copy != nullptr);
		REQUIRE(image_copy->width == image->width);
		REQUIRE(image_copy->height == image->height);
		REQUIRE(image_copy->bit_depth == image->bit_depth);
		REQUIRE(image_copy->color_type == image->color_type);
		REQUIRE(image_copy->bytes == image->bytes);
		delete image;
		delete image_copy;
	}
}
