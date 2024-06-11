#include "void_engine/window/window_manager.hpp"

#include "void_engine/window/window.hpp"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

using namespace void_engine::window;

TEST_CASE("Window_manager", "[window][window_manager]") {
	SECTION("Window manager init") {
		REQUIRE_NOTHROW(WindowManager::init());
	}

	SECTION("Window creation") {
		const Window* window = WindowManager::create("test", "Test", 800, 600);
		REQUIRE(window != nullptr);
	}

	SECTION("Window retrieval") {
		Window* window = nullptr;
		REQUIRE_NOTHROW(window = WindowManager::get("test"));
		REQUIRE(window != nullptr);
	}

	SECTION("Window retrieval failure") {
		REQUIRE_THROWS_AS(WindowManager::get("test2"), std::runtime_error);
	}

	SECTION("Window destruction") {
		REQUIRE_NOTHROW(WindowManager::destroy("test"));
	}

	SECTION("Window destruction failure") {
		REQUIRE_THROWS_AS(WindowManager::destroy("test"), std::runtime_error);
	}

	SECTION("Window manager terminate") {
		REQUIRE_NOTHROW(WindowManager::terminate());
	}
}
