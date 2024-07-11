#include "void_engine/event/event.hpp"
#include "void_engine/event/event_listener.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::event;

struct TestEvent {
	int data;
};

TEST_CASE("Event Listener", "[event][event_listener]") {
	const EventListener<TestEvent> event_listener([](const TestEvent& event) {
		REQUIRE(event.data == 10);
	});
	Event<TestEvent> event(TestEvent{10});
	event_listener.emit(&event);
}
