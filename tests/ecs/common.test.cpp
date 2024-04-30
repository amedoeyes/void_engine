#include "ecs/common.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace Void::ECS;

TEST_CASE("Entity", "[ecs][common]") {
	EntityIndex index = 10;
	EntityVersion version = 20;
	Entity entity = create_entity(index, version);

	SECTION("Entity creation") {
		REQUIRE(
			entity ==
			((static_cast<Entity>(index) << 32) | static_cast<Entity>(version))
		);
	}

	SECTION("Entity index") {
		REQUIRE(get_entity_index(entity) == index);
	}

	SECTION("Entity version") {
		REQUIRE(get_entity_version(entity) == version);
	}
}

TEST_CASE("Component", "[ecs][common]") {
	SECTION("Unique IDs for different types") {
		REQUIRE(get_component_id<int>() != get_component_id<float>());
		REQUIRE(get_component_id<double>() != get_component_id<int>());
		REQUIRE(get_component_id<float>() != get_component_id<double>());
	}

	SECTION("Same IDs for same types") {
		REQUIRE(get_component_id<int>() == get_component_id<int>());
		REQUIRE(get_component_id<float>() == get_component_id<float>());
		REQUIRE(get_component_id<double>() == get_component_id<double>());
	}
}
