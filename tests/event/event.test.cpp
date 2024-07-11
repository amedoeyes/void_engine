#include "void_engine/event/event.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace void_engine::event;

struct TestEvent {
	int data;
};

TEST_CASE("Event", "[event][event_test]") {
	const Event<TestEvent> event({10});
	REQUIRE(event.get_data().data == 10);
}
