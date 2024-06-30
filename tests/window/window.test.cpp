#include "void_engine/window/window.hpp"

#include "GLFW/glfw3.h"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::window;

TEST_CASE("Window", "[window][window]") {
	glfwInit();

	const Window window("Test", 800, 600);

	SECTION("Window is open") {
		REQUIRE_FALSE(window.should_close());
	}

	SECTION("Make context current") {
		window.make_context_current();
		REQUIRE(glfwGetCurrentContext() == window.get_window());
	}

	SECTION("Retrieve time") {
		const float time = window.get_time();
		while (window.get_time() - time < 1.0f) {
		}
		const float time2 = window.get_time();
		REQUIRE(time2 - time >= 1.0f);
	}

	SECTION("Retrieve delta time") {
		const float delta_time = window.get_delta_time();
		REQUIRE(delta_time >= 0.0f);
	}

	SECTION("Close window") {
		window.close();
		REQUIRE(window.should_close());
	}

	glfwTerminate();
}
