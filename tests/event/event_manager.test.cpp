#include "void_engine/event/event_manager.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::event;

struct TestEvent {
	int data;
};

TEST_CASE("Event Manager", "[event][event_manager]") {
	EventManager events;

	SECTION("Add listener and emit event") {
		events.add_listener<TestEvent>([](const TestEvent& event) {
			REQUIRE(event.data == 10);
		});
		events.emit(TestEvent{10});
		events.poll();
	}

	SECTION("Add listener and emit event multiple times") {
		events.add_listener<TestEvent>([](const TestEvent& event) {
			static int count;
			REQUIRE(event.data == 10 + count * 10);
			count++;
		});
		events.emit(TestEvent{10});
		events.emit(TestEvent{20});
		events.poll();
	}

	SECTION("Add multiple listeners and emit event") {
		events.add_listener<TestEvent>([&](const TestEvent& event) {
			REQUIRE(event.data == 10);
		});
		events.add_listener<TestEvent>([&](const TestEvent& event) {
			REQUIRE(event.data == 10);
		});
		events.emit(TestEvent{10});
		events.poll();
	}

	SECTION("Add multiple listeners and emit event multiple times") {
		events.add_listener<TestEvent>([&](const TestEvent& event) {
			static int count;
			REQUIRE(event.data == 10 + count * 10);
			count++;
		});
		events.add_listener<TestEvent>([&](const TestEvent& event) {
			static int count;
			REQUIRE(event.data == 10 + count * 10);
			count++;
		});
		events.emit(TestEvent{10});
		events.emit(TestEvent{20});
		events.poll();
	}

	SECTION("Remove listener") {
		int data = 0;
		auto* listener = events.add_listener<TestEvent>([&](const TestEvent& event) {
			data = event.data;
		});
		events.remove_listener<TestEvent>(listener);
		events.emit(TestEvent{10});
		events.poll();
		REQUIRE(data == 0);
	}

	SECTION("Remove event") {
		int data = 0;
		events.add_listener<TestEvent>([&](const TestEvent& event) {
			data = event.data;
		});
		events.emit(TestEvent{10});
		events.remove<TestEvent>();
		events.poll();
		REQUIRE(data == 0);
	}
}
