#include "void_engine/ecs/common.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ECS;

TEST_CASE("Common", "[ecs][common]") {
	const EntityIndex index = 10;
	const EntityVersion version = 20;
	const Entity entity = create_entity(index, version);

	SECTION("Create entity") {
		REQUIRE(
			entity ==
			((static_cast<Entity>(index) << 32) | static_cast<Entity>(version))
		);
	}

	SECTION("Retrieve entity index") {
		REQUIRE(get_entity_index(entity) == index);
	}

	SECTION("Retrieve entity version") {
		REQUIRE(get_entity_version(entity) == version);
	}

	SECTION("Retrieve uinque component ID") {
		REQUIRE(get_component_id<int>() != get_component_id<float>());
		REQUIRE(get_component_id<double>() != get_component_id<int>());
		REQUIRE(get_component_id<float>() != get_component_id<double>());
	}

	SECTION("Retrieve same component ID") {
		REQUIRE(get_component_id<int>() == get_component_id<int>());
		REQUIRE(get_component_id<float>() == get_component_id<float>());
		REQUIRE(get_component_id<double>() == get_component_id<double>());
	}
}
