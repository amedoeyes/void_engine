#include "void_engine/resources/image.hpp"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>

using namespace void_engine::resources;
namespace fs = std::filesystem;

TEST_CASE("Image", "[resources][image]") {
	fs::path image_path = fs::relative("../tests/resources/cat.png");

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
		REQUIRE(image->interlace_type == ImageInterlaceType::none);
		REQUIRE(image->compression_type == ImageCompressionType::base);
		REQUIRE(image->filter_method == ImageFilterMethod::base);
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
		const Image* image = read_image(image_path.string());
		REQUIRE(image != nullptr);
		write_image("cat_copy.png", image);
		const Image* image_copy = read_image("cat_copy.png");
		REQUIRE(image_copy != nullptr);
		REQUIRE(image_copy->width == image->width);
		REQUIRE(image_copy->height == image->height);
		REQUIRE(image_copy->bit_depth == image->bit_depth);
		REQUIRE(image_copy->color_type == image->color_type);
		REQUIRE(image_copy->interlace_type == image->interlace_type);
		REQUIRE(image_copy->compression_type == image->compression_type);
		REQUIRE(image_copy->filter_method == image->filter_method);
		REQUIRE(image_copy->bytes == image->bytes);
		delete image;
		delete image_copy;
	}
}
