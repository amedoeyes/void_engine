#include "void_engine/ecs/entity_manager.hpp"

#include "void_engine/ecs/entity.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ECS;

TEST_CASE("Entity Manager", "[ecs][entity_manager]") {
	EntityManager entites;

	SECTION("Create entity") {
		const Entity entity = entites.create();
		REQUIRE(entites.contains(entity));
	}

	SECTION("Destroy entity") {
		Entity entity = entites.create();
		entites.destroy(entity);
		REQUIRE_FALSE(entites.contains(entity));
		entity = entites.create();
		REQUIRE(get_entity_index(entity) == 0);
		REQUIRE(get_entity_version(entity) == 1);
	}

	SECTION("Check entity existence") {
		const Entity entity = entites.create();
		REQUIRE(entites.contains(entity));
		entites.destroy(entity);
		REQUIRE_FALSE(entites.contains(entity));
	}
}
