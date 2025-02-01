module void_engine.ecs;
import :entity;

namespace void_engine::ecs {

auto create_entity(EntityIndex index, EntityVersion version) -> Entity {
	return (static_cast<Entity>(index) << 32u) | static_cast<Entity>(version);
}

auto get_entity_index(Entity entity) -> EntityIndex { return (EntityIndex)(entity >> 32u); }

auto get_entity_version(Entity entity) -> EntityVersion { return (EntityVersion)(entity); }

} // namespace void_engine::ecs
