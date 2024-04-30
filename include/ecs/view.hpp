#ifndef VOID_ECS_VIEW_HPP
#define VOID_ECS_VIEW_HPP

#include <algorithm>

#include "ecs/common.hpp"
#include "ecs/pool_storage.hpp"

namespace Void::ECS {

template <typename... Components>
class View {
	public:
	View(const PoolStorage& pools) : _pools(pools) {
		if constexpr (sizeof...(Components) == 0) {
			_entities = _pools.get_entities();
		} else if constexpr (sizeof...(Components) == 1) {
			_entities = _pools.get_entities<typename std::tuple_element<
				0, std::tuple<Components...>>::type>();
		} else {
			std::vector<Entity> entities;
			auto check_smallest = [&](const std::vector<Entity>& pool) {
				if (entities.empty() || pool.size() < entities.size()) {
					entities = pool;
				}
			};
			(check_smallest(_pools.get_entities<Components>()), ...);

			entities.erase(
				std::remove_if(
					entities.begin(), entities.end(),
					[&](const Entity& entity) {
						return !(_pools.contains<Components>(entity) && ...);
					}
				),
				entities.end()
			);
			_entities = entities;
		}
	}

	std::vector<Entity>::iterator begin() {
		return _entities.begin();
	}

	std::vector<Entity>::iterator end() {
		return _entities.end();
	}

	private:
	const PoolStorage& _pools;
	std::vector<Entity> _entities;
};

}  // namespace Void::ECS

#endif	//! VOID_ECS_VIEW_HPP
