#include "void_engine/window/window.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::window;

TEST_CASE("Window", "[window][window]") {
	glfwInit();

	Window window("Test", 800, 600);

	SECTION("Window open") {
		REQUIRE(window.get_window() != nullptr);
		REQUIRE_FALSE(window.should_close());
	}

	SECTION("Close window") {
		window.close();
		REQUIRE(window.should_close());
	}
}
