#include "ecs/pool_storage.hpp"

#include <catch2/catch_test_macros.hpp>

#include "ecs/common.hpp"

using namespace Void::ECS;

struct Position {
	int x;
	int y;
};

struct Velocity {
	int x;
	int y;
};

TEST_CASE("PoolStorage", "[ecs][pool_storage]") {
	PoolStorage pools;

	SECTION("Create entity components") {
		Entity e = create_entity(0, 0);

		Position* p = pools.create<Position>(e, 10, 20);
		Velocity* v = pools.create<Velocity>(e, 30, 40);

		REQUIRE(p != nullptr);
		REQUIRE(p->x == 10);
		REQUIRE(p->y == 20);

		REQUIRE(v != nullptr);
		REQUIRE(v->x == 30);
		REQUIRE(v->y == 40);
	}

	SECTION("Get entity components") {
		Entity e = create_entity(0, 0);

		pools.create<Position>(e, 10, 20);
		pools.create<Velocity>(e, 30, 40);

		REQUIRE(pools.get_component<Position>(e) != nullptr);
		REQUIRE(pools.get_component<Position>(e)->x == 10);
		REQUIRE(pools.get_component<Position>(e)->y == 20);

		REQUIRE(pools.get_component<Velocity>(e) != nullptr);
		REQUIRE(pools.get_component<Velocity>(e)->x == 30);
		REQUIRE(pools.get_component<Velocity>(e)->y == 40);
	}

	SECTION("Check if entities exist") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pools.create<Position>(e1, 10, 20);
		pools.create<Velocity>(e2, 30, 40);

		REQUIRE(pools.contains<Position>(e1));
		REQUIRE_FALSE(pools.contains<Velocity>(e1));

		REQUIRE_FALSE(pools.contains<Position>(e2));
		REQUIRE(pools.contains<Velocity>(e2));
	}

	SECTION("Destroy entity") {
		Entity e = create_entity(0, 0);

		pools.create<Position>(e, 10, 20);
		pools.create<Velocity>(e, 30, 40);
		pools.destroy<Position>(e);

		REQUIRE_FALSE(pools.contains<Position>(e));
		REQUIRE(pools.get_component<Position>(e) == nullptr);

		REQUIRE(pools.contains<Velocity>(e));
		REQUIRE(pools.get_component<Velocity>(e)->x == 30);
		REQUIRE(pools.get_component<Velocity>(e)->y == 40);

		pools.create<Position>(e, 50, 60);
		pools.destroy(e);

		REQUIRE_FALSE(pools.contains<Position>(e));
		REQUIRE(pools.get_component<Position>(e) == nullptr);

		REQUIRE_FALSE(pools.contains<Velocity>(e));
		REQUIRE(pools.get_component<Velocity>(e) == nullptr);
	}

	SECTION("Clear entities") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);

		pools.create<Position>(e1, 10, 20);
		pools.create<Velocity>(e1, 30, 40);

		pools.create<Position>(e2, 50, 60);
		pools.create<Velocity>(e2, 70, 80);

		pools.clear<Position>();

		REQUIRE_FALSE(pools.contains<Position>(e1));
		REQUIRE(pools.get_component<Position>(e1) == nullptr);
		REQUIRE_FALSE(pools.contains<Position>(e2));
		REQUIRE(pools.get_component<Position>(e2) == nullptr);

		REQUIRE(pools.contains<Velocity>(e1));
		REQUIRE(pools.get_component<Velocity>(e1)->x == 30);
		REQUIRE(pools.get_component<Velocity>(e1)->y == 40);
		REQUIRE(pools.contains<Velocity>(e2));
		REQUIRE(pools.get_component<Velocity>(e2)->x == 70);
		REQUIRE(pools.get_component<Velocity>(e2)->y == 80);
	}

	SECTION("Get entities") {
		Entity e1 = create_entity(0, 0);
		Entity e2 = create_entity(1, 0);
		Entity e3 = create_entity(2, 0);
		Entity e4 = create_entity(3, 0);

		pools.create<Position>(e1, 10, 20);
		pools.create<Velocity>(e1, 30, 40);
		pools.create<Velocity>(e2, 30, 40);
		pools.create<Position>(e3, 50, 60);
		pools.create<Velocity>(e4, 70, 80);

		auto entities = pools.get_entities<Position>();
		REQUIRE(entities.size() == 2);
		REQUIRE(entities[0] == e1);
		REQUIRE(entities[1] == e3);

		entities = pools.get_entities<Velocity>();
		REQUIRE(entities.size() == 3);
		REQUIRE(entities[0] == e1);
		REQUIRE(entities[1] == e2);
		REQUIRE(entities[2] == e4);

		entities = pools.get_entities();
		REQUIRE(entities.size() == 4);
		REQUIRE(entities[0] == e1);
		REQUIRE(entities[1] == e2);
		REQUIRE(entities[2] == e3);
		REQUIRE(entities[3] == e4);
	}
}
