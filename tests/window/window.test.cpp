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

	SECTION("Make context current") {
		window.make_context_current();
		REQUIRE(glfwGetCurrentContext() == window.get_window());
	}

	SECTION("Get InputHandler") {
		REQUIRE(window.get_input_handler() != nullptr);
	}

	SECTION("Get time") {
		auto time = window.get_time();
		while (window.get_time() - time < 1.0f) {
		}
		auto time2 = window.get_time();
		REQUIRE(time2 - time >= 1.0f);
	}

	SECTION("Close window") {
		window.close();
		REQUIRE(window.should_close());
	}
}
