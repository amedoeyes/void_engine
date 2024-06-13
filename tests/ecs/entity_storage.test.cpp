#include "void_engine/ecs/entity_storage.hpp"

#include "void_engine/ecs/common.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ECS;

TEST_CASE("EntityStorage", "[ecs][entity_storage]") {
	EntityStorage storage;

	SECTION("Create entity") {
		const Entity e = storage.create();
		REQUIRE(storage.contains(e));
	}

	SECTION("Destroy entity") {
		Entity e = storage.create();
		storage.destroy(e);
		REQUIRE_FALSE(storage.contains(e));
		e = storage.create();
		REQUIRE(get_entity_version(e) == 1);
	}

	SECTION("Retrieve entity") {
		const Entity e = storage.create();
		REQUIRE(storage.get(get_entity_index(e)) == e);
	}

	SECTION("Check entity existence") {
		const Entity e = storage.create();
		REQUIRE(storage.contains(e));
		storage.destroy(e);
		REQUIRE_FALSE(storage.contains(e));
	}
}
