#include "void_engine/ecs/pool.hpp"

#include "void_engine/ecs/common.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ECS;

struct Position {
	int x;
	int y;
};

TEST_CASE("Pool", "[ecs][pool]") {
	Pool<Position> pool;

	SECTION("Create component") {
		const auto* p1 = pool.create(create_entity(0, 0), 10, 20);
		const auto* p2 = pool.create(create_entity(1, 0), 30, 40);
		REQUIRE(p1 != nullptr);
		REQUIRE(p1->x == 10);
		REQUIRE(p1->y == 20);
		REQUIRE(p2 != nullptr);
		REQUIRE(p2->x == 30);
		REQUIRE(p2->y == 40);
	}

	SECTION("Destroy component") {
		const Entity e1 = create_entity(0, 0);
		const Entity e2 = create_entity(1, 0);
		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);
		pool.destroy(e1);
		REQUIRE(pool.contains(e1) == false);
		REQUIRE(pool.get(e1) == nullptr);
		REQUIRE(pool.contains(e2) == true);
		REQUIRE(pool.get(e2) != nullptr);
		REQUIRE(pool.get(e2)->x == 30);
		REQUIRE(pool.get(e2)->y == 40);
	}

	SECTION("Retrieve component") {
		const Entity e1 = create_entity(0, 0);
		const Entity e2 = create_entity(1, 0);
		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);
		const auto* p1 = pool.get(e1);
		const auto* p2 = pool.get(e2);
		REQUIRE(p1 != nullptr);
		REQUIRE(p1->x == 10);
		REQUIRE(p1->y == 20);
		REQUIRE(p2 != nullptr);
		REQUIRE(p2->x == 30);
		REQUIRE(p2->y == 40);
	}

	SECTION("Check component existence") {
		const Entity e1 = create_entity(0, 0);
		const Entity e2 = create_entity(1, 0);
		pool.create(e1, 10, 20);
		REQUIRE(pool.contains(e1) == true);
		REQUIRE(pool.contains(e2) == false);
	}

	SECTION("Retrieve entities") {
		const Entity e1 = create_entity(0, 0);
		const Entity e2 = create_entity(1, 0);
		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);
		const std::vector<Entity>& entities = pool.get_entities();
		REQUIRE(entities.size() == 2);
		REQUIRE(entities[0] == e1);
		REQUIRE(entities[1] == e2);
	}

	SECTION("Clear pool") {
		const Entity e1 = create_entity(0, 0);
		const Entity e2 = create_entity(1, 0);
		pool.create(e1, 10, 20);
		pool.create(e2, 30, 40);
		pool.clear();
		REQUIRE(pool.contains(e1) == false);
		REQUIRE(pool.get(e1) == nullptr);
		REQUIRE(pool.contains(e2) == false);
		REQUIRE(pool.get(e2) == nullptr);
	}
}
