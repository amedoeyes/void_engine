#include "void_engine/ecs/common.hpp"

namespace void_engine::ECS {

Entity create_entity(const EntityIndex& index, const EntityVersion& version) {
	return (static_cast<Entity>(index) << 32) | static_cast<Entity>(version);
}

EntityIndex get_entity_index(const Entity& entity) {
	return (EntityIndex)(entity >> 32);
}

EntityVersion get_entity_version(const Entity& entity) {
	return (EntityVersion)(entity);
}

}  // namespace void_engine::ECS
