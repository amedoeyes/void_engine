#include "ecs/entity_storage.hpp"

#include <catch2/catch_test_macros.hpp>

#include "ecs/common.hpp"

using namespace void_engine::ECS;

TEST_CASE("EntityStorage", "[ecs][entity_storage]") {
	EntityStorage storage;

	SECTION("Entity creation") {
		Entity e = storage.create();
		REQUIRE(storage.contains(e));
	}

	SECTION("Entity destruction") {
		Entity e = storage.create();
		storage.destroy(e);
		REQUIRE_FALSE(storage.contains(e));
		e = storage.create();
		REQUIRE(get_entity_version(e) == 1);
	}

	SECTION("Entity retrieval") {
		Entity e = storage.create();
		REQUIRE(storage.get(get_entity_index(e)) == e);
	}

	SECTION("Entity containment") {
		Entity e = storage.create();
		REQUIRE(storage.contains(e));
		storage.destroy(e);
		REQUIRE_FALSE(storage.contains(e));
	}
}
