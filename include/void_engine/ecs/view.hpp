#ifndef VOID_ENGINE_ECS_VIEW_HPP
#define VOID_ENGINE_ECS_VIEW_HPP

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/pool_storage.hpp"

#include <algorithm>

namespace void_engine::ECS {

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
					[&](Entity entity) {
						return !(_pools.contains<Components>(entity) && ...);
					}
				),
				entities.end()
			);
			_entities = entities;
		}
	}

	auto begin() -> std::vector<Entity>::iterator {
		return _entities.begin();
	}

	auto end() -> std::vector<Entity>::iterator {
		return _entities.end();
	}

private:
	const PoolStorage& _pools;
	std::vector<Entity> _entities;
};

} // namespace void_engine::ECS

#endif //! VOID_ENGINE_ECS_VIEW_HPP
