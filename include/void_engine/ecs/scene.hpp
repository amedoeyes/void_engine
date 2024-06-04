#ifndef VOID_ENGINE_ECS_SCENE_HPP
#define VOID_ENGINE_ECS_SCENE_HPP

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/entity_storage.hpp"
#include "void_engine/ecs/pool_storage.hpp"
#include "void_engine/ecs/view.hpp"

#include <tuple>

namespace void_engine::ECS {

class Scene {
public:
	auto create() -> Entity;
	void destroy(Entity entity);

	template <typename Component, typename... Args>
	auto attach(Entity entity, Args&&... args) -> Component* {
		if (!_entities.contains(entity)) return nullptr;
		return _pools.create<Component>(entity, std::forward<Args>(args)...);
	}

	template <typename... Components>
	auto attach_all(Entity entity) -> std::tuple<Components*...> {
		return std::make_tuple(attach<Components>(entity)...);
	}

	template <typename Component>
	void remove(Entity entity) {
		if (!_entities.contains(entity)) return;
		_pools.destroy<Component>(entity);
	}

	template <typename... Components>
	void remove_all(Entity entity) {
		(remove<Components>(entity), ...);
	}

	template <typename Component>
	auto fetch(Entity entity) -> Component* {
		if (!_entities.contains(entity)) return nullptr;
		return _pools.get_component<Component>(entity);
	}

	template <typename... Components>
	auto fetch_all(Entity entity) -> std::tuple<Components*...> {
		return std::make_tuple(fetch<Components>(entity)...);
	}

	template <typename Component>
	auto has(Entity entity) -> bool {
		if (!_entities.contains(entity)) return false;
		return _pools.contains<Component>(entity);
	}

	template <typename... Components>
	auto has_all(Entity entity) -> bool {
		return (has<Components>(entity) && ...);
	}

	template <typename... Components>
	auto view() -> View<Components...> {
		return View<Components...>(_pools);
	}

private:
	EntityStorage _entities;
	PoolStorage _pools;
};

} // namespace void_engine::ECS

#endif //! VOID_ENGINE_ECS_SCENE_HPP
