#ifndef VOID_ECS_COMMON_HPP
#define VOID_ECS_COMMON_HPP

#include <bitset>
#include <cstdint>

using EntityIndex = uint32_t;
using EntityVersion = uint32_t;
using EntityID = uint64_t;
using ComponentID = uint16_t;

const EntityID MAX_ENTITIES = 1024;
const ComponentID MAX_COMPONENTS = 32;

using Mask = std::bitset<MAX_COMPONENTS>;

inline ComponentID component_counter() {
	static ComponentID counter = 0;
	return counter++;
}

template <typename T>
ComponentID get_component_id() {
	static ComponentID id = component_counter();
	return id;
}

namespace Void::ECS {

using Entity = EntityID;

}  // namespace Void::ECS

#endif	// !VOID_ECS_COMMON_HPP
