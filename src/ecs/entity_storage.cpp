#include "void_engine/ecs/entity_storage.hpp"

#include "void_engine/ecs/common.hpp"

namespace void_engine::ECS {

Entity EntityStorage::create() {
	if (!_free.empty()) {
		Entity free_index = _free.back();
		_free.pop_back();
		Entity entity = create_entity(
			free_index, get_entity_version(_data[free_index]) + 1
		);
		_data[free_index] = entity;
		return entity;
	}

	Entity entity = create_entity(_data.size(), 0);
	_data.push_back(entity);
	return entity;
}

void EntityStorage::destroy(const Entity& entity) {
	_data[get_entity_index(entity)] =
		create_entity(INVALID_ENTITY_INDEX, get_entity_version(entity));
	_free.push_back(entity);
}

Entity EntityStorage::get(const EntityIndex& index) const {
	if (index >= _data.size()) return INVALID_ENTITY;
	return _data[index];
}

bool EntityStorage::contains(const Entity& entity) const {
	return _data[get_entity_index(entity)] == entity;
}

}  // namespace void_engine::ECS
