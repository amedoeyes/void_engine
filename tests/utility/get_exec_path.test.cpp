#include "void_engine/utility/get_exec_path.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::utility;

TEST_CASE("Get Executable Path", "[utility][get_exec_path]") {
	REQUIRE_FALSE(get_exec_path().empty());
}
