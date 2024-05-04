#include "ecs/view.hpp"

#include <catch2/catch_test_macros.hpp>

#include "ecs/common.hpp"
#include "ecs/pool_storage.hpp"

using namespace void_engine::ECS;

struct Position {
	int x;
	int y;
};

struct Velocity {
	int x;
	int y;
};

TEST_CASE("View", "[ecs][view]") {
	PoolStorage pools;

	Entity e1 = create_entity(0, 0);
	pools.create<Position>(e1, 10, 20);
	pools.create<Velocity>(e1, 30, 40);
	Entity e2 = create_entity(1, 0);
	pools.create<Position>(e2, 40, 50);
	pools.create<Velocity>(e2, 60, 70);
	Entity e3 = create_entity(2, 0);
	pools.create<Position>(e3, 80, 90);
	Entity e4 = create_entity(3, 0);
	pools.create<Velocity>(e4, 100, 110);

	SECTION("View with no components") {
		View view(pools);
		REQUIRE(view.begin() != view.end());

		int count = 0;
		for (auto e : view) {
			if (count == 0) {
				REQUIRE(pools.contains<Position>(e));
				REQUIRE(pools.get_component<Position>(e)->x == 10);
				REQUIRE(pools.get_component<Position>(e)->y == 20);
				REQUIRE(pools.contains<Velocity>(e));
				REQUIRE(pools.get_component<Velocity>(e)->x == 30);
				REQUIRE(pools.get_component<Velocity>(e)->y == 40);
			} else if (count == 1) {
				REQUIRE(pools.contains<Position>(e));
				REQUIRE(pools.get_component<Position>(e)->x == 40);
				REQUIRE(pools.get_component<Position>(e)->y == 50);
				REQUIRE(pools.contains<Velocity>(e));
				REQUIRE(pools.get_component<Velocity>(e)->x == 60);
				REQUIRE(pools.get_component<Velocity>(e)->y == 70);
			} else if (count == 2) {
				REQUIRE(pools.contains<Position>(e));
				REQUIRE(pools.get_component<Position>(e)->x == 80);
				REQUIRE(pools.get_component<Position>(e)->y == 90);
			} else {
				REQUIRE(pools.contains<Velocity>(e));
				REQUIRE(pools.get_component<Velocity>(e)->x == 100);
				REQUIRE(pools.get_component<Velocity>(e)->y == 110);
			}
			count++;
		}
		REQUIRE(count == 4);
	}

	SECTION("View with one component") {
		View<Position> view(pools);
		REQUIRE(view.begin() != view.end());

		int count = 0;
		for (auto e : view) {
			REQUIRE(pools.contains<Position>(e));
			if (count == 0) {
				REQUIRE(pools.get_component<Position>(e)->x == 10);
				REQUIRE(pools.get_component<Position>(e)->y == 20);
			} else if (count == 1) {
				REQUIRE(pools.get_component<Position>(e)->x == 40);
				REQUIRE(pools.get_component<Position>(e)->y == 50);
			} else {
				REQUIRE(pools.get_component<Position>(e)->x == 80);
				REQUIRE(pools.get_component<Position>(e)->y == 90);
			}
			count++;
		}
		REQUIRE(count == 3);
	}

	SECTION("View with multiple components") {
		View<Position, Velocity> view(pools);
		REQUIRE(view.begin() != view.end());

		int count = 0;
		for (auto e : view) {
			REQUIRE(pools.contains<Position>(e));
			REQUIRE(pools.contains<Velocity>(e));

			if (count == 0) {
				REQUIRE(pools.get_component<Position>(e)->x == 10);
				REQUIRE(pools.get_component<Position>(e)->y == 20);
				REQUIRE(pools.get_component<Velocity>(e)->x == 30);
				REQUIRE(pools.get_component<Velocity>(e)->y == 40);
			} else {
				REQUIRE(pools.get_component<Position>(e)->x == 40);
				REQUIRE(pools.get_component<Position>(e)->y == 50);
				REQUIRE(pools.get_component<Velocity>(e)->x == 60);
				REQUIRE(pools.get_component<Velocity>(e)->y == 70);
			}
			count++;
		}
		REQUIRE(count == 2);
	}
}
