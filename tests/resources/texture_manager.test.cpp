#include "void_engine/resources/texture_manager.hpp"

#include "void_engine/renderer/renderer.hpp"
#include "void_engine/window/window_manager.hpp"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>

using namespace void_engine::resources;
using namespace void_engine::renderer;
using namespace void_engine::window;

namespace fs = std::filesystem;

TEST_CASE("Image", "[resources][texture_manager]") {
	WindowManager::init();
	WindowManager::create("test", "test", 800, 600);
	Renderer::init();
	fs::path image_path = fs::relative("../tests/resources/cat.png");

	SECTION("Create 2D texture") {
		const Texture* texture =
			TextureManager::create_2d("test", image_path.string());
		REQUIRE(texture != nullptr);
	}

	SECTION("Get texture") {
		const Texture* texture = TextureManager::get("test");
		REQUIRE(texture != nullptr);
	}

	SECTION("Destroy texture") {
		TextureManager::destroy("test");
		REQUIRE_THROWS_AS(TextureManager::get("test"), std::runtime_error);
	}

	SECTION("Terminate texture manager") {
		TextureManager::create_2d("test", image_path.string());
		TextureManager::terminate();
		REQUIRE_THROWS_AS(TextureManager::get("test"), std::runtime_error);
	}

	WindowManager::terminate();
}
