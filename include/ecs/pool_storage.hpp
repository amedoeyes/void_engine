#ifndef VOID_ECS_POOL_SComponentORAGE_HPP
#define VOID_ECS_POOL_SComponentORAGE_HPP

#include <unordered_map>

#include "ecs/common.hpp"
#include "ecs/pool.hpp"
#include "ecs/pool_base.hpp"

namespace void_engine::ECS {

class PoolStorage {
	public:
	~PoolStorage();

	public:
	template <typename Component, typename... Args>
	Component* create(const Entity& entity, Args&&... args) {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) {
			_pools[id] = new Pool<Component>();
		}
		return static_cast<Pool<Component>*>(_pools[id])
			->create(entity, std::forward<Args>(args)...);
	}

	template <typename Component>
	void destroy(const Entity& entity) {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return;
		static_cast<Pool<Component>*>(_pools[id])->destroy(entity);
	}

	void destroy(const Entity& entity);

	template <typename Component>
	void clear() {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return;
		static_cast<Pool<Component>*>(_pools[id])->clear();
	}

	template <typename Component>
	Component* get_component(const Entity& entity) {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return nullptr;
		return static_cast<Pool<Component>*>(_pools[id])->get(entity);
	}

	template <typename Component>
	const std::vector<Entity>& get_entities() const {
		static const std::vector<Entity>& empty = {};
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return empty;
		return static_cast<Pool<Component>*>(_pools.at(id))->get_entities();
	}

	const std::vector<Entity> get_entities() const;

	template <typename Component>
	bool contains(const Entity& entity) const {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return false;
		return static_cast<Pool<Component>*>(_pools.at(id))->contains(entity);
	}

	private:
	std::unordered_map<ComponentID, PoolBase*> _pools;
};

}  // namespace void_engine::ECS

#endif	// !VOID_ECS_POOL_SComponentORAGE_HPP
