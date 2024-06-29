#include "void_engine/event/event_listener.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::event;

struct TestEvent {
	int data;
};

TEST_CASE("Event Listener", "[event][event_listener]") {
	EventListener<TestEvent> event_listener([](const TestEvent& event) {
		REQUIRE(event.data == 10);
	});
	const TestEvent test_event{10};
	Event<TestEvent> event(test_event);
	event_listener.emit(&event);
}
