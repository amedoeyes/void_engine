#include "void_engine/ecs/entity_manager.hpp"

#include "void_engine/ecs/entity.hpp"

namespace void_engine::ecs {

auto EntityManager::create() -> Entity {
	if (!_free.empty()) {
		const EntityIndex& free_index = _free.front();
		_free.pop();
		return _data[free_index];
	}
	const Entity entity = create_entity(_data.size(), 0);
	_data.push_back(entity);
	return entity;
}

void EntityManager::destroy(Entity entity) {
	const EntityIndex index = get_entity_index(entity);
	_data[index]++;
	_free.push(index);
}

auto EntityManager::contains(Entity entity) const -> bool {
	return _data[get_entity_index(entity)] == entity;
}

} // namespace void_engine::ecs
