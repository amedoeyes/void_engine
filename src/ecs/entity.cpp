#include "void_engine/ecs/entity.hpp"

namespace void_engine::ECS {

auto create_entity(EntityIndex index, EntityVersion version) -> Entity {
	return (static_cast<Entity>(index) << 32) | static_cast<Entity>(version);
}

auto get_entity_index(Entity entity) -> EntityIndex {
	return (EntityIndex)(entity >> 32);
}

auto get_entity_version(Entity entity) -> EntityVersion {
	return (EntityVersion)(entity);
}

} // namespace void_engine::ECS
