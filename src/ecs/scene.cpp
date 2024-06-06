#include "void_engine/ecs/scene.hpp"

#include "void_engine/ecs/common.hpp"

namespace void_engine::ECS {

auto Scene::create() -> Entity {
	return _entities.create();
}

void Scene::destroy(Entity entity) {
	if (!_entities.contains(entity)) return;
	_pools.destroy(entity);
	_entities.destroy(entity);
}

} // namespace void_engine::ECS
