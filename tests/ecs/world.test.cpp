#include "void_engine/ecs/world.hpp"

#include "void_engine/ecs/entity.hpp"

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

TEST_CASE("World", "[ecs][world]") {
	World world;

	SECTION("Create entity") {
		const Entity e1 = world.create();
		const Entity e2 = world.create();
		REQUIRE(get_entity_index(e1) == 0);
		REQUIRE(get_entity_version(e1) == 0);
		REQUIRE(get_entity_index(e2) == 1);
		REQUIRE(get_entity_version(e2) == 0);
	}

	SECTION("create entity with components") {
		const Entity e = world.create<Position, Velocity>();
		REQUIRE(world.has<Position, Velocity>(e));
	}

	SECTION("Create entity with components with braces") {
		const Entity e = world.create(Position{10, 20}, Velocity{30, 40});
		REQUIRE(world.has<Position, Velocity>(e));
		REQUIRE(world.fetch<Position>(e).x == 10);
		REQUIRE(world.fetch<Position>(e).y == 20);
		REQUIRE(world.fetch<Velocity>(e).x == 30);
		REQUIRE(world.fetch<Velocity>(e).y == 40);
	}

	SECTION("Destroy entity") {
		const Entity e = world.create();
		REQUIRE(world.contains(e));
		world.destroy(e);
		REQUIRE_FALSE(world.contains(e));
	}

	SECTION("Check if entity exists") {
		REQUIRE(world.contains(world.create()));
		REQUIRE_FALSE(world.contains(42));
	}

	SECTION("Attach component to entity") {
		const Entity e = world.create();
		world.attach<Position>(e) = {10, 20};
		REQUIRE(world.has<Position>(e));
		REQUIRE(world.fetch<Position>(e).x == 10);
		REQUIRE(world.fetch<Position>(e).y == 20);
	}

	SECTION("Attach component with braces to entity") {
		const Entity e = world.create();
		world.attach(e, Position{10, 20});
		REQUIRE(world.has<Position>(e));
		REQUIRE(world.fetch<Position>(e).x == 10);
		REQUIRE(world.fetch<Position>(e).y == 20);
	}

	SECTION("Attach multiple components to entity") {
		const Entity e = world.create();
		auto [p1, v1] = world.attach<Position, Velocity>(e);
		p1 = {10, 20};
		v1 = {30, 40};
		REQUIRE(world.has<Position, Velocity>(e));
		auto [p2, v2] = world.fetch<Position, Velocity>(e);
		REQUIRE(p2.x == 10);
		REQUIRE(p2.y == 20);
		REQUIRE(v2.x == 30);
		REQUIRE(v2.y == 40);
	}

	SECTION("Attach multiple components with braces to entity") {
		const Entity e = world.create();
		world.attach(e, Position{10, 20}, Velocity{30, 40});
		REQUIRE(world.has<Position, Velocity>(e));
		auto [p, v] = world.fetch<Position, Velocity>(e);
		REQUIRE(p.x == 10);
		REQUIRE(p.y == 20);
		REQUIRE(v.x == 30);
		REQUIRE(v.y == 40);
	}

	SECTION("Detach component from entity") {
		const Entity e = world.create<Position, Velocity>();
		world.detach<Position>(e);
		REQUIRE_FALSE(world.has<Position>(e));
		REQUIRE(world.has<Velocity>(e));
	}

	SECTION("Detach multiple components from entity") {
		const Entity e = world.create<Position, Velocity>();
		world.detach<Position, Velocity>(e);
		REQUIRE_FALSE(world.has<Position>(e));
		REQUIRE_FALSE(world.has<Velocity>(e));
	}

	SECTION("Fetch entity component") {
		const Entity e = world.create(Position{10, 20}, Velocity{30, 40});
		REQUIRE(world.has<Position, Velocity>(e));
		auto p = world.fetch<Position>(e);
		auto v = world.fetch<Velocity>(e);
		REQUIRE(p.x == 10);
		REQUIRE(p.y == 20);
		REQUIRE(v.x == 30);
		REQUIRE(v.y == 40);
	}

	SECTION("Fetch multiple entity components") {
		const Entity e = world.create(Position{10, 20}, Velocity{30, 40});
		const auto [p, v] = world.fetch<Position, Velocity>(e);
		REQUIRE(world.has<Position, Velocity>(e));
		REQUIRE(p.x == 10);
		REQUIRE(p.y == 20);
		REQUIRE(v.x == 30);
		REQUIRE(v.y == 40);
	}

	SECTION("Entity has component") {
		const Entity e = world.create<Position>();
		REQUIRE(world.has<Position>(e));
	}

	SECTION("Entity has multiple components") {
		const Entity e = world.create<Position, Velocity>();
		REQUIRE(world.has<Position, Velocity>(e));
		world.detach<Position, Velocity>(e);
		REQUIRE_FALSE(world.has<Position, Velocity>(e));
	}

	SECTION("Query all entities") {
		const Entity e1 = world.create<Position>();
		const Entity e2 = world.create<Velocity>();
		const auto& entities = world.query();
		REQUIRE(entities.size() == 2);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e1) != entities.end()
		);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e2) != entities.end()
		);
	}

	SECTION("Query entities with component") {
		const Entity e = world.create<Position>();
		world.create<Velocity>();
		const auto& entities = world.query<Position>();
		REQUIRE(entities.size() == 1);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e) != entities.end()
		);
	}

	SECTION("Query entities with multiple components") {
		const Entity e = world.create<Position, Velocity>();
		world.create<Position>();
		const auto& entities = world.query<Position, Velocity>();
		REQUIRE(entities.size() == 1);
		REQUIRE(
			std::find(entities.begin(), entities.end(), e) != entities.end()
		);
	}
}
