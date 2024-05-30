#ifndef VOID_ENGINE_ECS_SCENE_HPP
#define VOID_ENGINE_ECS_SCENE_HPP

#include <tuple>

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/entity_storage.hpp"
#include "void_engine/ecs/pool_storage.hpp"
#include "void_engine/ecs/view.hpp"

namespace void_engine::ECS {

class Scene {
	public:
	Entity create();
	void destroy(Entity entity);

	template <typename Component, typename... Args>
	Component* attach(Entity entity, Args&&... args) {
		if (!_entities.contains(entity)) return nullptr;
		return _pools.create<Component>(entity, std::forward<Args>(args)...);
	}

	template <typename... Components>
	std::tuple<Components*...> attach_all(Entity entity) {
		return std::make_tuple(attach<Components>(entity)...);
	}

	template <typename Component>
	void remove(Entity entity) {
		if (!_entities.contains(entity)) return;
		_pools.destroy<Component>(entity);
	}

	template <typename Component>
	Component* fetch(Entity entity) {
		if (!_entities.contains(entity)) return nullptr;
		return _pools.get_component<Component>(entity);
	}

	template <typename... Components>
	std::tuple<Components*...> fetch_all(Entity entity) {
		return std::make_tuple(fetch<Components>(entity)...);
	}

	template <typename... Components>
	View<Components...> view() {
		return View<Components...>(_pools);
	}

	template <typename Component>
	bool has(Entity entity) {
		if (!_entities.contains(entity)) return false;
		return _pools.contains<Component>(entity);
	}

	template <typename... Components>
	bool has_all(Entity entity) {
		return (has<Components>(entity) && ...);
	}

	private:
	EntityStorage _entities;
	PoolStorage _pools;
};

}  // namespace void_engine::ECS

#endif	//! VOID_ENGINE_ECS_SCENE_HPP
