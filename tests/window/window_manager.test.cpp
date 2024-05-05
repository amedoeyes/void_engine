#include "void_engine/window/window_manager.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::window;

TEST_CASE("Window_manager", "[window][window_manager]") {
	SECTION("Window manager init") {
		REQUIRE_NOTHROW(WindowManager::init());
	}

	SECTION("Window creation") {
		auto window = WindowManager::create("Test", 800, 600);
		REQUIRE(window != nullptr);
		REQUIRE_FALSE(window->should_close());
	}

	SECTION("Window destruction") {
		auto window = WindowManager::create("Test", 800, 600);
		WindowManager::destroy(window);
	}

	SECTION("Window manager terminate") {
		REQUIRE_NOTHROW(WindowManager::terminate());
	}
}
