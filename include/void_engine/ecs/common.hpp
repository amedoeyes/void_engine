#ifndef VOID_ENGINE_ECS_COMMON_HPP
#define VOID_ENGINE_ECS_COMMON_HPP

#include <cstdint>

namespace void_engine::ECS {

using Entity = uint64_t;
using EntityIndex = uint32_t;
using EntityVersion = uint32_t;

constexpr Entity INVALID_ENTITY = Entity(-1);
constexpr EntityIndex INVALID_ENTITY_INDEX = EntityIndex(-1);

auto create_entity(EntityIndex index, EntityVersion version) -> Entity;
auto get_entity_index(Entity entity) -> EntityIndex;
auto get_entity_version(Entity entity) -> EntityVersion;

using ComponentID = uint16_t;

inline auto component_counter() -> ComponentID {
	static ComponentID counter = 0;
	return counter++;
}

template <typename T>
auto get_component_id() -> ComponentID {
	static ComponentID id = component_counter();
	return id;
}

} // namespace void_engine::ECS

#endif // !VOID_ENGINE_ECS_COMMON_HPP
