#ifndef VOID_ECS_SCENE_HPP
#define VOID_ECS_SCENE_HPP

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/entity_storage.hpp"
#include "void_engine/ecs/pool_storage.hpp"
#include "void_engine/ecs/view.hpp"

namespace void_engine::ECS {

class Scene {
	public:
	Entity create();
	void destroy(const Entity& entity);

	template <typename Component, typename... Args>
	Component* add(const Entity& entity, Args&&... args) {
		if (!_entities.contains(entity)) return nullptr;
		return _pools.create<Component>(entity, std::forward<Args>(args)...);
	}

	template <typename Component>
	void remove(const Entity& entity) {
		if (!_entities.contains(entity)) return;
		_pools.destroy<Component>(entity);
	}

	template <typename Component>
	Component* get(const Entity& entity) {
		if (!_entities.contains(entity)) return nullptr;
		return _pools.get_component<Component>(entity);
	}

	template <typename... Components>
	View<Components...> view() {
		return View<Components...>(_pools);
	}

	private:
	EntityStorage _entities;
	PoolStorage _pools;
};

}  // namespace void_engine::ECS

#endif	//! VOID_ECS_SCENE_HPP
