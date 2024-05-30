#include "void_engine/ecs/scene.hpp"

#include <catch2/catch_test_macros.hpp>

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/view.hpp"

using namespace void_engine::ECS;

struct Position {
	int x;
	int y;
};

struct Velocity {
	int x;
	int y;
};

TEST_CASE("View", "[ecs][scene]") {
	Scene scene;

	SECTION("Create and destroy entities") {
		Entity e = scene.create();
		Position* p = scene.attach<Position>(e, 10, 20);
		Velocity* v = scene.attach<Velocity>(e, 30, 40);

		REQUIRE(p != nullptr);
		REQUIRE(p->x == 10);
		REQUIRE(p->y == 20);

		REQUIRE(v != nullptr);
		REQUIRE(v->x == 30);
		REQUIRE(v->y == 40);

		scene.destroy(e);

		REQUIRE(scene.fetch<Position>(e) == nullptr);
		REQUIRE(scene.fetch<Velocity>(e) == nullptr);
	}

	SECTION("Fetch entity components") {
		Entity e = scene.create();
		scene.attach<Position>(e, 10, 20);
		scene.attach<Velocity>(e, 30, 40);

		REQUIRE(scene.fetch<Position>(e) != nullptr);
		REQUIRE(scene.fetch<Position>(e)->x == 10);
		REQUIRE(scene.fetch<Position>(e)->y == 20);

		REQUIRE(scene.fetch<Velocity>(e) != nullptr);
		REQUIRE(scene.fetch<Velocity>(e)->x == 30);
		REQUIRE(scene.fetch<Velocity>(e)->y == 40);
	}

	SECTION("Remove entity components") {
		Entity e = scene.create();
		scene.attach<Position>(e, 10, 20);
		scene.attach<Velocity>(e, 30, 40);

		scene.remove<Position>(e);
		REQUIRE(scene.fetch<Position>(e) == nullptr);
		scene.remove<Velocity>(e);
		REQUIRE(scene.fetch<Velocity>(e) == nullptr);
	}

	Entity e1 = scene.create();
	scene.attach<Position>(e1, 10, 20);
	scene.attach<Velocity>(e1, 30, 40);
	Entity e2 = scene.create();
	scene.attach<Position>(e2, 40, 50);
	scene.attach<Velocity>(e2, 60, 70);
	Entity e3 = scene.create();
	scene.attach<Position>(e3, 80, 90);
	Entity e4 = scene.create();
	scene.attach<Velocity>(e4, 100, 110);

	SECTION("View with no components returns all entities") {
		auto view = scene.view();
		REQUIRE(view.begin() != view.end());

		int count = 0;
		for (auto e : view) {
			if (count == 0) {
				REQUIRE(scene.fetch<Position>(e)->x == 10);
				REQUIRE(scene.fetch<Position>(e)->y == 20);
				REQUIRE(scene.fetch<Velocity>(e)->x == 30);
				REQUIRE(scene.fetch<Velocity>(e)->y == 40);
			} else if (count == 1) {
				REQUIRE(scene.fetch<Position>(e)->x == 40);
				REQUIRE(scene.fetch<Position>(e)->y == 50);
				REQUIRE(scene.fetch<Velocity>(e)->x == 60);
				REQUIRE(scene.fetch<Velocity>(e)->y == 70);
			} else if (count == 2) {
				REQUIRE(scene.fetch<Position>(e)->x == 80);
				REQUIRE(scene.fetch<Position>(e)->y == 90);
			} else {
				REQUIRE(scene.fetch<Velocity>(e)->x == 100);
				REQUIRE(scene.fetch<Velocity>(e)->y == 110);
			}
			count++;
		}
		REQUIRE(count == 4);
	}

	SECTION("View with one component") {
		auto view = scene.view<Position>();
		REQUIRE(view.begin() != view.end());

		int count = 0;
		for (auto e : view) {
			if (count == 0) {
				REQUIRE(scene.fetch<Position>(e)->x == 10);
				REQUIRE(scene.fetch<Position>(e)->y == 20);
			} else if (count == 1) {
				REQUIRE(scene.fetch<Position>(e)->x == 40);
				REQUIRE(scene.fetch<Position>(e)->y == 50);
			} else {
				REQUIRE(scene.fetch<Position>(e)->x == 80);
				REQUIRE(scene.fetch<Position>(e)->y == 90);
			}
			count++;
		}
		REQUIRE(count == 3);
	}

	SECTION("View with multiple components") {
		auto view = scene.view<Position, Velocity>();
		REQUIRE(view.begin() != view.end());

		int count = 0;
		for (auto e : view) {
			if (count == 0) {
				REQUIRE(scene.fetch<Position>(e)->x == 10);
				REQUIRE(scene.fetch<Position>(e)->y == 20);
				REQUIRE(scene.fetch<Velocity>(e)->x == 30);
				REQUIRE(scene.fetch<Velocity>(e)->y == 40);
			} else {
				REQUIRE(scene.fetch<Position>(e)->x == 40);
				REQUIRE(scene.fetch<Position>(e)->y == 50);
				REQUIRE(scene.fetch<Velocity>(e)->x == 60);
				REQUIRE(scene.fetch<Velocity>(e)->y == 70);
			}
			count++;
		}
		REQUIRE(count == 2);
	}
}
