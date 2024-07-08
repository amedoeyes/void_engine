#include "void_engine/ecs/component_pool.hpp"

#include "void_engine/ecs/entity.hpp"
#include "void_engine/ecs/entity_manager.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ECS;

struct Position {
	int x;
	int y;
};

TEST_CASE("Component Pool", "[ecs][component_pool]") {
	ComponentPool<Position> pool;
	EntityManager entities;

	SECTION("Create component") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		pool.create(e1) = {10, 20};
		pool.create(e2) = {30, 40};
		const auto& p1 = pool.get(e1);
		const auto& p2 = pool.get(e2);
		REQUIRE(p1.x == 10);
		REQUIRE(p1.y == 20);
		REQUIRE(p2.x == 30);
		REQUIRE(p2.y == 40);
	}

	SECTION("Create component multiple times") {
		const Entity e = entities.create();
		pool.create(e) = {10, 20};
		pool.create(e) = {30, 40};
		const auto& p1 = pool.get(e);
		const auto& p2 = pool.get(e);
		REQUIRE(p1.x == 30);
		REQUIRE(p1.y == 40);
		REQUIRE(p2.x == 30);
		REQUIRE(p2.y == 40);
	}

	SECTION("Create component with braces") {
		const auto& p1 = pool.create(entities.create(), {10, 20});
		const auto& p2 = pool.create(entities.create(), {30, 40});
		REQUIRE(p1.x == 10);
		REQUIRE(p1.y == 20);
		REQUIRE(p2.x == 30);
		REQUIRE(p2.y == 40);
	}

	SECTION("Create component with braces multiple times") {
		const Entity e = entities.create();
		const auto& p1 = pool.create(e, {10, 20});
		const auto& p2 = pool.create(e, {30, 40});
		REQUIRE(p1.x == 30);
		REQUIRE(p1.y == 40);
		REQUIRE(p2.x == 30);
		REQUIRE(p2.y == 40);
	}

	SECTION("Destroy component") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		pool.create(e1, {10, 20});
		pool.create(e2, {30, 40});
		pool.destroy(e1);
		REQUIRE(pool.contains(e1) == false);
		REQUIRE(pool.contains(e2) == true);
		REQUIRE(pool.get(e2).x == 30);
		REQUIRE(pool.get(e2).y == 40);
	}

	SECTION("Clear pool") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		pool.create(e1, {10, 20});
		pool.create(e2, {30, 40});
		pool.clear();
		REQUIRE(pool.contains(e1) == false);
		REQUIRE(pool.contains(e2) == false);
	}

	SECTION("Get component") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		pool.create(e1, {10, 20});
		pool.create(e2, {30, 40});
		const auto& p1 = pool.get(e1);
		const auto& p2 = pool.get(e2);
		REQUIRE(p1.x == 10);
		REQUIRE(p1.y == 20);
		REQUIRE(p2.x == 30);
		REQUIRE(p2.y == 40);
	}

	SECTION("Check component existence") {
		const Entity e = entities.create();
		pool.create(e, {10, 20});
		REQUIRE(pool.contains(e) == true);
		REQUIRE(pool.contains(entities.create()) == false);
	}
}
