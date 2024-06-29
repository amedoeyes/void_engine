#include "void_engine/event/event.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::event;

struct TestEvent {
	int data;
};

TEST_CASE("Event", "[event][event]") {
	const TestEvent test_event{10};
	Event<TestEvent> event(test_event);
	REQUIRE(event.get_data().data == test_event.data);
}
