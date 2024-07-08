#ifndef VOID_ENGINE_ECS_TYPES_HPP
#define VOID_ENGINE_ECS_TYPES_HPP

#include <cstdint>

namespace void_engine::ECS {

using Entity = uint64_t;
using EntityIndex = uint32_t;
using EntityVersion = uint32_t;

auto create_entity(EntityIndex index, EntityVersion version) -> Entity;
auto get_entity_index(Entity entity) -> EntityIndex;
auto get_entity_version(Entity entity) -> EntityVersion;

} // namespace void_engine::ECS

#endif // !VOID_ENGINE_ECS_TYPES_HPP
