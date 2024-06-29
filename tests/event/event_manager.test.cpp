#include "void_engine/event/event_manager.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::event;

struct TestEvent {
	int data;
};

TEST_CASE("Event Manager", "[event][event_manager]") {
	EventManager event_manager;

	SECTION("Add listener and emit event") {
		event_manager.add_listener<TestEvent>([](const TestEvent& event) {
			REQUIRE(event.data == 10);
		});
		event_manager.emit<TestEvent>(10);
		event_manager.poll();
	}

	SECTION("Add listener and emit event multiple times") {
		event_manager.add_listener<TestEvent>([](const TestEvent& event) {
			static int count;
			REQUIRE(event.data == 10 + count * 10);
			count++;
		});
		event_manager.emit<TestEvent>(10);
		event_manager.emit<TestEvent>(20);
		event_manager.poll();
	}

	SECTION("Add multiple listeners and emit event") {
		event_manager.add_listener<TestEvent>([&](const TestEvent& event) {
			REQUIRE(event.data == 10);
		});
		event_manager.add_listener<TestEvent>([&](const TestEvent& event) {
			REQUIRE(event.data == 10);
		});
		event_manager.emit<TestEvent>(10);
		event_manager.poll();
	}

	SECTION("Add multiple listeners and emit event multiple times") {
		event_manager.add_listener<TestEvent>([&](const TestEvent& event) {
			static int count;
			REQUIRE(event.data == 10 + count * 10);
			count++;
		});
		event_manager.add_listener<TestEvent>([&](const TestEvent& event) {
			static int count;
			REQUIRE(event.data == 10 + count * 10);
			count++;
		});
		event_manager.emit<TestEvent>(10);
		event_manager.emit<TestEvent>(20);
		event_manager.poll();
	}

	SECTION("Remove listener") {
		int data = 0;
		auto listener =
			event_manager.add_listener<TestEvent>([&](const TestEvent& event) {
				data = event.data;
			});
		event_manager.remove_listener<TestEvent>(listener);
		event_manager.emit<TestEvent>(10);
		event_manager.poll();
		REQUIRE(data == 0);
	}

	SECTION("Remove event") {
		int data = 0;
		event_manager.add_listener<TestEvent>([&](const TestEvent& event) {
			data = event.data;
		});
		event_manager.emit<TestEvent>(10);
		event_manager.remove<TestEvent>();
		event_manager.poll();
		REQUIRE(data == 0);
	}
}
