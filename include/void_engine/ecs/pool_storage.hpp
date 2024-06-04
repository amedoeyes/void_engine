#ifndef VOID_ENGINE_ECS_POOL_STORAGE_HPP
#define VOID_ENGINE_ECS_POOL_STORAGE_HPP

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/pool.hpp"
#include "void_engine/ecs/pool_base.hpp"

#include <unordered_map>

namespace void_engine::ECS {

class PoolStorage {
public:
	~PoolStorage();

public:
	template <typename Component, typename... Args>
	auto create(Entity entity, Args&&... args) -> Component* {
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
	auto get_component(Entity entity) -> Component* {
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return nullptr;
		return pool->get(entity);
	}

	template <typename Component>
	auto get_entities() const -> const std::vector<Entity>& {
		static const std::vector<Entity>& empty = {};
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return empty;
		return pool->get_entities();
	}

	auto get_entities() const -> const std::vector<Entity>;

	template <typename Component>
	auto contains(Entity entity) const -> bool {
		Pool<Component>* pool = get_pool<Component>();
		if (pool == nullptr) return false;
		return pool->contains(entity);
	}

private:
	std::unordered_map<ComponentID, PoolBase*> _pools;

private:
	template <typename Component>
	auto get_or_create_pool() -> Pool<Component>* {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) _pools[id] = new Pool<Component>();
		return static_cast<Pool<Component>*>(_pools[id]);
	}
	template <typename Component>
	auto get_pool() const -> Pool<Component>* {
		ComponentID id = get_component_id<Component>();
		if (_pools.find(id) == _pools.end()) return nullptr;
		return static_cast<Pool<Component>*>(_pools.at(id));
	}
};

} // namespace void_engine::ECS

#endif // !VOID_ENGINE_ECS_POOL_STORAGE_HPP
