#include "void_engine/ecs/scene.hpp"

#include "void_engine/ecs/common.hpp"

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

TEST_CASE("Scene", "[ecs][scene]") {
	Scene scene;

	SECTION("Create entity") {
		const Entity e = scene.create();
		REQUIRE(e != INVALID_ENTITY);
	}

	SECTION("Attach component to entity") {
		const Entity e = scene.create();
		scene.attach<Position>(e, 10, 20);
		REQUIRE(scene.has<Position>(e));
		REQUIRE(scene.fetch<Position>(e) != nullptr);
		REQUIRE(scene.fetch<Position>(e)->x == 10);
		REQUIRE(scene.fetch<Position>(e)->y == 20);
	}

	SECTION("Attach multiple components to entity") {
		const Entity e = scene.create();
		const auto [p, v] = scene.attach_all<Position, Velocity>(e);
		REQUIRE(scene.has_all<Position, Velocity>(e));
		REQUIRE(p != nullptr);
		REQUIRE(v != nullptr);
	}

	SECTION("Fetch entity component") {
		const Entity e = scene.create();
		scene.attach<Position>(e, 10, 20);
		scene.attach<Velocity>(e, 30, 40);
		REQUIRE(scene.has_all<Position, Velocity>(e));
		auto p = scene.fetch<Position>(e);
		auto v = scene.fetch<Velocity>(e);
		REQUIRE(p != nullptr);
		REQUIRE(p->x == 10);
		REQUIRE(p->y == 20);
		REQUIRE(v != nullptr);
		REQUIRE(v->x == 30);
		REQUIRE(v->y == 40);
	}

	SECTION("Fetch multiple entity components") {
		const Entity e = scene.create();
		scene.attach<Position>(e, 10, 20);
		scene.attach<Velocity>(e, 30, 40);
		const auto [p, v] = scene.fetch_all<Position, Velocity>(e);
		REQUIRE(scene.has_all<Position, Velocity>(e));
		REQUIRE(p != nullptr);
		REQUIRE(p->x == 10);
		REQUIRE(p->y == 20);
		REQUIRE(v != nullptr);
		REQUIRE(v->x == 30);
		REQUIRE(v->y == 40);
	}

	SECTION("Remove entity component") {
		const Entity e = scene.create();
		scene.attach<Position>(e);
		REQUIRE(scene.has<Position>(e));
		scene.remove<Position>(e);
		REQUIRE_FALSE(scene.has<Position>(e));
		const auto p = scene.fetch<Position>(e);
		REQUIRE(p == nullptr);
	}

	SECTION("Remove multiple entity components") {
		const Entity e = scene.create();
		scene.attach_all<Position, Velocity>(e);
		REQUIRE(scene.has_all<Position, Velocity>(e));
		scene.remove_all<Position, Velocity>(e);
		REQUIRE_FALSE(scene.has_all<Position, Velocity>(e));
		const auto [p, v] = scene.fetch_all<Position, Velocity>(e);
		REQUIRE(p == nullptr);
		REQUIRE(v == nullptr);
	}

	SECTION("Entity has component") {
		const Entity e = scene.create();
		scene.attach<Position>(e, 10, 20);
		REQUIRE(scene.has<Position>(e));
	}

	SECTION("Entity has multiple components") {
		const Entity e = scene.create();
		scene.attach_all<Position, Velocity>(e);
		REQUIRE(scene.has_all<Position, Velocity>(e));
		scene.remove_all<Position, Velocity>(e);
		REQUIRE_FALSE(scene.has_all<Position, Velocity>(e));
	}
}
