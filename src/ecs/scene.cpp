#include "ecs/scene.hpp"

using namespace Void::ECS;

Scene::~Scene() {
	for (Pool* p : _pools) {
		delete p;
	}
}

Entity Scene::create() {
	_masks.emplace_back();
	return _entities.create();
}

void Scene::destroy(const Entity& id) {
	if (!_entities.exists(id)) return;
	_masks[_entities.get_index(id)].reset();
	_entities.destroy(id);
}
