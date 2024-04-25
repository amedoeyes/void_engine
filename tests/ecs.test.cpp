#include <catch2/catch_test_macros.hpp>

#include "ecs/common.hpp"
#include "ecs/entity_storage.hpp"
#include "ecs/scene.hpp"
#include "ecs/scene_view.hpp"

TEST_CASE("EntityStorage", "[ECS]") {
	using namespace Void::ECS;

	EntityStorage storage;

	SECTION("Create") {
		EntityID id1 = storage.create();
		REQUIRE(id1 == 0);
		EntityID id2 = storage.create();
		REQUIRE(id2 == 4294967296);
		EntityID id3 = storage.create();
		REQUIRE(id3 == 8589934592);
		storage.destroy(id1);
		id1 = storage.create();
		REQUIRE(id1 == 1);
	}

	SECTION("Destroy") {
		EntityID id = storage.create();
		REQUIRE(storage.exists(id));
		storage.destroy(id);
		REQUIRE_FALSE(storage.exists(id));
	}

	SECTION("Size") {
		REQUIRE(storage.size() == 0);
		storage.create();
		REQUIRE(storage.size() == 1);
		storage.create();
		REQUIRE(storage.size() == 2);
		storage.destroy(storage.create());
		REQUIRE(storage.size() == 3);
	}

	SECTION("Get") {
		EntityID id = storage.create();
		REQUIRE(storage.get(storage.get_index(id)) == id);
		storage.destroy(id);
		REQUIRE_FALSE(storage.is_valid(storage.get(storage.get_index(id))));
	}

	SECTION("GetIndex") {
		EntityID id = storage.create();
		REQUIRE(storage.get_index(id) == 0);
		EntityID id2 = storage.create();
		REQUIRE(storage.get_index(id2) == 1);
		EntityID id3 = storage.create();
		REQUIRE(storage.get_index(id3) == 2);
	}

	SECTION("GetVersion") {
		EntityID id = storage.create();
		REQUIRE(storage.get_version(id) == 0);
		storage.destroy(id);
		id = storage.create();
		REQUIRE(storage.get_version(id) == 1);
	}

	SECTION("Exists") {
		EntityID id = storage.create();
		REQUIRE(storage.exists(id));
		storage.destroy(id);
		REQUIRE_FALSE(storage.exists(id));
	}
}

TEST_CASE("Scene", "[ECS]") {
	using namespace Void::ECS;

	Scene scene;

	struct Postion {
		float x, y;
	};
	struct Velocity {
		float x, y;
	};

	SECTION("Create") {
		Entity id1 = scene.create();
		REQUIRE(id1 == 0);
		Entity id2 = scene.create();
		REQUIRE(id2 == 4294967296);
		Entity id3 = scene.create();
		REQUIRE(id3 == 8589934592);
		scene.destroy(id1);
		id1 = scene.create();
		REQUIRE(id1 == 1);
	}

	SECTION("Add") {
		Entity id = scene.create();
		Postion* pos = scene.add<Postion>(id, 1.0f, 2.0f);
		REQUIRE(pos->x == 1.0f);
		REQUIRE(pos->y == 2.0f);
		Velocity* vel = scene.add<Velocity>(id, 3.0f, 4.0f);
		REQUIRE(vel->x == 3.0f);
		REQUIRE(vel->y == 4.0f);
	}

	SECTION("Destroy") {
		Entity id = scene.create();
		REQUIRE(id == 0);
		scene.add<Postion>(id, 1.0f, 2.0f);
		scene.destroy(id);
		REQUIRE(scene.get<Postion>(id) == nullptr);
		id = scene.create();
		REQUIRE(id == 1);
		REQUIRE(scene.get<Postion>(id) == nullptr);
	}

	SECTION("get") {
		Entity id = scene.create();
		scene.add<Postion>(id, 1.0f, 2.0f);
		Postion* pos = scene.get<Postion>(id);
		REQUIRE(pos->x == 1.0f);
		REQUIRE(pos->y == 2.0f);
		scene.destroy(id);
		REQUIRE(scene.get<Postion>(id) == nullptr);
	}
}

TEST_CASE("SceneView", "[ECS]") {
	using namespace Void::ECS;

	Scene scene;

	struct Postion {
		float x, y;
	};
	struct Velocity {
		float x, y;
	};

	Entity id1 = scene.create();
	scene.add<Postion>(id1, 1.0f, 2.0f);
	scene.add<Velocity>(id1, 3.0f, 4.0f);
	Entity id2 = scene.create();
	scene.add<Postion>(id2, 5.0f, 6.0f);
	scene.add<Velocity>(id2, 7.0f, 8.0f);
	Entity id3 = scene.create();
	scene.add<Postion>(id3, 9.0f, 10.0f);
	Entity id4 = scene.create();
	scene.add<Velocity>(id4, 11.0f, 12.0f);

	int count = 0;
	for (const auto& id : SceneView<Postion, Velocity>(scene)) {
		if (count == 0) {
			REQUIRE(id == id1);
			Postion* pos = scene.get<Postion>(id);
			REQUIRE(pos->x == 1.0f);
			REQUIRE(pos->y == 2.0f);
			Velocity* vel = scene.get<Velocity>(id);
			REQUIRE(vel->x == 3.0f);
			REQUIRE(vel->y == 4.0f);
		} else {
			REQUIRE(id == id2);
			Postion* pos = scene.get<Postion>(id);
			REQUIRE(pos->x == 5.0f);
			REQUIRE(pos->y == 6.0f);
			Velocity* vel = scene.get<Velocity>(id);
			REQUIRE(vel->x == 7.0f);
			REQUIRE(vel->y == 8.0f);
		}
		count++;
	}
	REQUIRE(count == 2);

	count = 0;
	for (const auto& id : SceneView<Postion>(scene)) {
		if (count == 0) {
			REQUIRE(id == id1);
			Postion* pos = scene.get<Postion>(id);
			REQUIRE(pos->x == 1.0f);
			REQUIRE(pos->y == 2.0f);
		} else if (count == 1) {
			REQUIRE(id == id2);
			Postion* pos = scene.get<Postion>(id);
			REQUIRE(pos->x == 5.0f);
			REQUIRE(pos->y == 6.0f);
		} else {
			REQUIRE(id == id3);
			Postion* pos = scene.get<Postion>(id);
			REQUIRE(pos->x == 9.0f);
			REQUIRE(pos->y == 10.0f);
		}
		count++;
	}
	REQUIRE(count == 3);

	count = 0;
	for (const auto& id : SceneView<Velocity>(scene)) {
		if (count == 0) {
			REQUIRE(id == id1);
			Velocity* vel = scene.get<Velocity>(id);
			REQUIRE(vel->x == 3.0f);
			REQUIRE(vel->y == 4.0f);
		} else if (count == 1) {
			REQUIRE(id == id2);
			Velocity* vel = scene.get<Velocity>(id);
			REQUIRE(vel->x == 7.0f);
			REQUIRE(vel->y == 8.0f);
		} else {
			REQUIRE(id == id4);
			Velocity* vel = scene.get<Velocity>(id);
			REQUIRE(vel->x == 11.0f);
			REQUIRE(vel->y == 12.0f);
		}
		count++;
	}
	REQUIRE(count == 3);
}
