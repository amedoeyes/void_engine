#include "void_engine/ecs/scene.hpp"

namespace void_engine::ECS {

Entity Scene::create() {
	return _entities.create();
}

void Scene::destroy(Entity entity) {
	if (!_entities.contains(entity)) return;
	_pools.destroy(entity);
	_entities.destroy(entity);
}

}  // namespace void_engine::ECS
