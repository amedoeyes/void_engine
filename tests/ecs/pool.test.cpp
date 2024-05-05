#include "void_engine/ecs/pool.hpp"

#include <catch2/catch_test_macros.hpp>

#include "void_engine/ecs/common.hpp"

using namespace void_engine::ECS;

struct Position {
	int x;
	int y;
};

TEST_CASE("Pool", "[ecs][pool]") {
	Pool<Position> pool;

	SECTION("Create and get entity component") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);

		REQUIRE(pool.get(e1) != nullptr);
		REQUIRE(pool.get(e1)->x == 10);
		REQUIRE(pool.get(e1)->y == 20);
		REQUIRE(pool.get(e2) != nullptr);
		REQUIRE(pool.get(e2)->x == 30);
		REQUIRE(pool.get(e2)->y == 40);

		pool.create(e1, 50, 60);

		REQUIRE(pool.get(e1) != nullptr);
		REQUIRE(pool.get(e1)->x == 50);
		REQUIRE(pool.get(e1)->y == 60);
	}

	SECTION("Check if entity exist") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pool.create(e1, 10, 20);

		REQUIRE(pool.contains(e1) == true);
		REQUIRE(pool.contains(e2) == false);
	}

	SECTION("Destroy entity") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);

		pool.destroy(e1);

		REQUIRE(pool.contains(e1) == false);
		REQUIRE(pool.get(e1) == nullptr);
		REQUIRE(pool.contains(e2) == true);
		REQUIRE(pool.get(e2)->x == 30);
		REQUIRE(pool.get(e2)->y == 40);
	}

	SECTION("Clear entities") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);
		pool.clear();

		REQUIRE(pool.contains(e1) == false);
		REQUIRE(pool.get(e1) == nullptr);
		REQUIRE(pool.contains(e2) == false);
		REQUIRE(pool.get(e2) == nullptr);
	}

	SECTION("Get entities") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);

		const auto& entities = pool.get_entities();

		REQUIRE(entities.size() == 2);
		REQUIRE(entities[0] == e1);
		REQUIRE(entities[1] == e2);
	}
}
