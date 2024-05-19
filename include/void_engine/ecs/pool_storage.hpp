#ifndef VOID_ENGINE_ECS_POOL_STORAGE_HPP
#define VOID_ENGINE_ECS_POOL_STORAGE_HPP

#include <unordered_map>

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/pool.hpp"
#include "void_engine/ecs/pool_base.hpp"

namespace void_engine::ECS {

class PoolStorage {
	public:
	~PoolStorage();

	public:
	template <typename Component, typename... Args>
	Component* create(Entity entity, Args&&... args) {
		Pool<Component>* pool = get_or_create_pool<Component>();
		return pool->create(entity, std::forward<Args>(args)...);
	}

	template <typename Component>
	void destroy(Entity entity) {
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return;
		pool->destroy(entity);
	}

	void destroy(Entity entity);

	template <typename Component>
	void clear() {
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return;
		pool->clear();
	}

	template <typename Component>
	Component* get_component(Entity entity) {
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return nullptr;
		return pool->get(entity);
	}

	template <typename Component>
	const std::vector<Entity>& get_entities() const {
		static const std::vector<Entity>& empty = {};
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return empty;
		return pool->get_entities();
	}

	const std::vector<Entity> get_entities() const;

	template <typename Component>
	bool contains(Entity entity) const {
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return false;
		return pool->contains(entity);
	}

	private:
	std::unordered_map<ComponentID, PoolBase*> _pools;

	private:
	template <typename Component>
	Pool<Component>* get_or_create_pool() {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) _pools[id] = new Pool<Component>();
		return static_cast<Pool<Component>*>(_pools[id]);
	}
	template <typename Component>
	Pool<Component>* get_pool() const {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return nullptr;
		return static_cast<Pool<Component>*>(_pools.at(id));
	}
};

}  // namespace void_engine::ECS

#endif	// !VOID_ENGINE_ECS_POOL_STORAGE_HPP
