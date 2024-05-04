#ifndef VOID_ECS_COMMON_HPP
#define VOID_ECS_COMMON_HPP

#include <cstdint>

namespace void_engine::ECS {

using Entity = uint64_t;
using EntityIndex = uint32_t;
using EntityVersion = uint32_t;

constexpr Entity INVALID_ENTITY = Entity(-1);
constexpr EntityIndex INVALID_ENTITY_INDEX = EntityIndex(-1);

Entity create_entity(const EntityIndex& index, const EntityVersion& version);
EntityIndex get_entity_index(const Entity& entity);
EntityVersion get_entity_version(const Entity& entity);

using ComponentID = uint16_t;

inline ComponentID component_counter() {
	static ComponentID counter = 0;
	return counter++;
}

template <typename T>
ComponentID get_component_id() {
	static ComponentID id = component_counter();
	return id;
}

}  // namespace void_engine::ECS

#endif	// !VOID_ECS_COMMON_HPP
