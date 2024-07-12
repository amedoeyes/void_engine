#include "void_engine/ecs/entity.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ecs;

TEST_CASE("Entity", "[ecs][entity]") {
	const EntityIndex index = 10;
	const EntityVersion version = 20;
	const Entity entity = create_entity(index, version);

	SECTION("Create entity") {
		REQUIRE(entity == ((static_cast<Entity>(index) << 32u) | static_cast<Entity>(version)));
	}

	SECTION("Get entity index") {
		REQUIRE(get_entity_index(entity) == index);
	}

	SECTION("Get entity version") {
		REQUIRE(get_entity_version(entity) == version);
	}
}
