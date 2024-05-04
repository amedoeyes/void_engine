#include "ecs/pool_storage.hpp"

#include <algorithm>

using namespace void_engine::ECS;

PoolStorage::~PoolStorage() {
	for (auto& [_, pool] : _pools) {
		delete pool;
	}
}

void PoolStorage::destroy(const Entity& entity) {
	for (auto& [_, pool] : _pools) {
		pool->destroy(entity);
	}
}

const std::vector<Entity> PoolStorage::get_entities() const {
	size_t size = 0;

	for (auto& [_, pool] : _pools) {
		size += pool->get_entities().size();
	}

	std::vector<Entity> entities;
	entities.reserve(size);

	for (auto& [_, pool] : _pools) {
		auto& pool_entities = pool->get_entities();
		entities.insert(
			entities.end(), pool_entities.begin(), pool_entities.end()
		);
	}

	std::sort(entities.begin(), entities.end());
	entities.erase(
		std::unique(entities.begin(), entities.end()), entities.end()
	);

	return entities;
}
