#include "ecs/scene.hpp"

namespace Void::ECS {

Entity Scene::create() {
	return _entities.create();
}

void Scene::destroy(const Entity& entity) {
	if (!_entities.contains(entity)) return;
	_pools.destroy(entity);
	_entities.destroy(entity);
}

}  // namespace Void::ECS
