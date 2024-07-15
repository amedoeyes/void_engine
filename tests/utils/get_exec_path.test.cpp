#include "void_engine/utils/get_exec_path.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::utils;

TEST_CASE("Get Executable Path", "[utils][get_exec_path]") {
	REQUIRE_FALSE(void_engine::utils::get_exec_path().empty());
}
