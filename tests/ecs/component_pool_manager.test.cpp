#include "void_engine/ecs/component_pool_manager.hpp"

#include "void_engine/ecs/entity.hpp"
#include "void_engine/ecs/entity_manager.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::ECS;

struct Position {
	int x;
	int y;
};

struct Velocity {
	int x;
	int y;
};

TEST_CASE("Component Pool Manager", "[ecs][component_pool_manager]") {
	ComponentPoolManager pools;
	EntityManager entities;

	SECTION("Create entity component") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		const auto& p1 = pools.create<Position>(e1) = {10, 20};
		const auto& v1 = pools.create<Velocity>(e1) = {30, 40};
		const auto& p2 = pools.create<Position>(e2) = {50, 60};
		const auto& v2 = pools.create<Velocity>(e2) = {70, 80};
		REQUIRE(p1.x == 10);
		REQUIRE(p1.y == 20);
		REQUIRE(v1.x == 30);
		REQUIRE(v1.y == 40);
		REQUIRE(p2.x == 50);
		REQUIRE(p2.y == 60);
		REQUIRE(v2.x == 70);
		REQUIRE(v2.y == 80);
	}

	SECTION("Create entity component with braces") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		const auto& p1 = pools.create(e1, Position{10, 20});
		const auto& v1 = pools.create(e1, Velocity{30, 40});
		const auto& p2 = pools.create(e2, Position{50, 60});
		const auto& v2 = pools.create(e2, Velocity{70, 80});
		REQUIRE(p1.x == 10);
		REQUIRE(p1.y == 20);
		REQUIRE(v1.x == 30);
		REQUIRE(v1.y == 40);
		REQUIRE(p2.x == 50);
		REQUIRE(p2.y == 60);
		REQUIRE(v2.x == 70);
		REQUIRE(v2.y == 80);
	}

	SECTION("Destroy entity's component") {
		const Entity e = entities.create();
		pools.create(e, Position{10, 20});
		pools.create(e, Velocity{30, 40});
		pools.destroy<Position>(e);
		REQUIRE_FALSE(pools.contains<Position>(e));
		REQUIRE(pools.contains<Velocity>(e));
		REQUIRE(pools.get<Velocity>(e).x == 30);
		REQUIRE(pools.get<Velocity>(e).y == 40);
	}

	SECTION("Destroy all entity's components") {
		const Entity e = entities.create();
		pools.create(e, Position{10, 20});
		pools.create(e, Velocity{30, 40});
		pools.destroy(e);
		REQUIRE_FALSE(pools.contains<Position>(e));
		REQUIRE_FALSE(pools.contains<Velocity>(e));
	}

	SECTION("Clear components") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		pools.create(e1, Position{10, 20});
		pools.create(e1, Velocity{30, 40});
		pools.create(e2, Position{50, 60});
		pools.create(e2, Velocity{70, 80});
		pools.clear<Position>();
		REQUIRE_FALSE(pools.contains<Position>(e1));
		REQUIRE_FALSE(pools.contains<Position>(e2));
		REQUIRE(pools.contains<Velocity>(e1));
		REQUIRE(pools.get<Velocity>(e1).x == 30);
		REQUIRE(pools.get<Velocity>(e1).y == 40);
		REQUIRE(pools.contains<Velocity>(e2));
		REQUIRE(pools.get<Velocity>(e2).x == 70);
		REQUIRE(pools.get<Velocity>(e2).y == 80);
	}

	SECTION("Get component") {
		const Entity e = entities.create();
		pools.create(e, Position{10, 20});
		pools.create(e, Velocity{30, 40});
		const auto& p = pools.get<Position>(e);
		const auto& v = pools.get<Velocity>(e);
		REQUIRE(p.x == 10);
		REQUIRE(p.y == 20);
		REQUIRE(v.x == 30);
		REQUIRE(v.y == 40);
	}

	SECTION("Check if a component pool contains entity") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		pools.create<Position>(e1);
		pools.create<Velocity>(e2);
		REQUIRE(pools.contains<Position>(e1));
		REQUIRE_FALSE(pools.contains<Velocity>(e1));
		REQUIRE_FALSE(pools.contains<Position>(e2));
		REQUIRE(pools.contains<Velocity>(e2));
	}

	SECTION("Check if multiple component pools contain entity") {
		struct Test {};
		const Entity e = entities.create();
		pools.create<Position>(e);
		pools.create<Velocity>(e);
		REQUIRE(pools.contains<Position, Velocity>(e));
		REQUIRE_FALSE(pools.contains<Position, Velocity, Test>(e));
	}

	SECTION("Get all entities") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		const Entity e3 = entities.create();
		const Entity e4 = entities.create();
		pools.create<Position>(e1);
		pools.create<Velocity>(e2);
		pools.create<Position>(e3);
		pools.create<Velocity>(e4);
		const std::vector<Entity> entities = pools.query();
		REQUIRE(entities.size() == 4);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e1) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e2) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e3) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e4) != entities.end()
		);
	}

	SECTION("Get entities with component") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		const Entity e3 = entities.create();
		const Entity e4 = entities.create();
		pools.create<Position>(e1);
		pools.create<Velocity>(e1);
		pools.create<Position>(e2);
		pools.create<Velocity>(e2);
		pools.create<Velocity>(e3);
		pools.create<Position>(e4);
		const std::vector<Entity>& entities = pools.query<Position>();
		REQUIRE(entities.size() == 3);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e1) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e2) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e4) != entities.end()
		);
	}

	SECTION("Get entities with multiple components") {
		const Entity e1 = entities.create();
		const Entity e2 = entities.create();
		const Entity e3 = entities.create();
		const Entity e4 = entities.create();
		pools.create<Position>(e1);
		pools.create<Velocity>(e1);
		pools.create<Position>(e2);
		pools.create<Velocity>(e2);
		pools.create<Position>(e3);
		pools.create<Velocity>(e3);
		pools.create<Position>(e4);
		const std::vector<Entity>& entities = pools.query<Position, Velocity>();
		REQUIRE(entities.size() == 3);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e1) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e2) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e3) != entities.end()
		);
	}
}
