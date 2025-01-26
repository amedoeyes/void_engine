export module void_engine.ecs:entity;

import std;

export namespace void_engine::ecs {

using Entity = std::uint64_t;
using EntityIndex = std::uint32_t;
using EntityVersion = std::uint32_t;

auto create_entity(EntityIndex index, EntityVersion version) -> Entity;
auto get_entity_index(Entity entity) -> EntityIndex;
auto get_entity_version(Entity entity) -> EntityVersion;

} // namespace void_engine::ecs
