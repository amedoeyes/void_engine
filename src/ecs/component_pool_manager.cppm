module;

#include <cassert>

export module void_engine.ecs:component_pool.manager;

import :component_pool;
import :component_pool.base;
import :entity;

import std;

export namespace void_engine::ecs {

using ComponentID = std::uint16_t;

class ComponentPoolManager {
public:
	ComponentPoolManager(const ComponentPoolManager&) = default;
	ComponentPoolManager(ComponentPoolManager&&) = delete;
	auto operator=(const ComponentPoolManager&) -> ComponentPoolManager& = default;
	auto operator=(ComponentPoolManager&&) -> ComponentPoolManager& = delete;
	ComponentPoolManager() = default;
	~ComponentPoolManager() {
		for (auto& [_, pool] : _pools) {
			delete pool;
		}
	}

	template <typename Component>
	auto create(Entity entity) -> Component& {
		auto* pool = get_or_create_pool<Component>();
		return pool->create(entity);
	}

	template <typename Component>
	auto create(Entity entity, Component&& component) -> Component& {
		auto* pool = get_or_create_pool<Component>();
		return pool->create(entity, std::forward<Component>(component));
	}

	template <typename Component>
	void destroy(Entity entity) {
		auto* pool = get_pool<Component>();
		assert(pool != nullptr && "Component pool does not exist");
		pool->destroy(entity);
	}

	void destroy(Entity entity) {
		for (const auto& [_, pool] : _pools) {
			if (pool->contains(entity)) {
				pool->destroy(entity);
			}
		}
	}

	template <typename Component>
	void clear() {
		auto* pool = get_pool<Component>();
		assert(pool != nullptr && "Component pool does not exist");
		pool->clear();
	}

	template <typename Component>
	[[nodiscard]] auto get(Entity entity) -> Component& {
		auto* pool = get_pool<Component>();
		assert(pool != nullptr && "Component pool does not exist");
		return pool->get(entity);
	}

	template <typename Component>
	[[nodiscard]] auto contains(Entity entity) const -> bool {
		auto* pool = get_pool<Component>();
		if (pool == nullptr) {
			return false;
		}
		return pool->contains(entity);
	}

	template <typename... Components>
		requires(sizeof...(Components) > 1)
	[[nodiscard]] auto contains(Entity entity) const -> bool {
		return (contains<Components>(entity) && ...);
	}

	[[nodiscard]] auto query() const -> std::vector<Entity> {
		std::unordered_set<Entity> unique;
		for (const auto& [_, pool] : _pools) {
			const auto& pool_entities = pool->get_entities();
			unique.insert(pool_entities.begin(), pool_entities.end());
		}
		std::vector<Entity> entities;
		entities.reserve(unique.size());
		std::ranges::move(unique, std::back_inserter(entities));
		return entities;
	}

	template <typename Component>
	[[nodiscard]] auto query() const -> const std::vector<Entity>& {
		static const std::vector<Entity> empty;
		auto* pool = get_pool<Component>();
		if (pool == nullptr) {
			return empty;
		}
		return pool->get_entities();
	}

	template <typename... Components>
		requires(sizeof...(Components) > 1)
	[[nodiscard]] auto query() const -> std::vector<Entity> {
		const std::array<const std::vector<Entity>*, sizeof...(Components)> pools = {&query<Components>(
		)...};
		const std::vector<Entity>* smallest_pool = pools[0];
		for (const auto& pool : pools) {
			if (pool->size() < smallest_pool->size()) {
				smallest_pool = pool;
			}
		}
		std::vector<Entity> entities;
		for (const auto& entity : *smallest_pool) {
			if (contains<Components...>(entity)) {
				entities.push_back(entity);
			}
		}
		return entities;
	}

private:
	std::unordered_map<ComponentID, ComponentPoolBase*> _pools;

	[[nodiscard]] static auto component_counter() -> ComponentID {
		static ComponentID counter = 0;
		return counter++;
	}

	template <typename Component>
	[[nodiscard]] auto get_component_id() const -> ComponentID {
		static const ComponentID id = component_counter();
		return id;
	}

	template <typename Component>
	[[nodiscard]] auto get_or_create_pool() -> ComponentPool<Component>* {
		ComponentID id = get_component_id<Component>();
		const auto it = _pools.find(id);
		if (it == _pools.end()) {
			_pools[id] = new ComponentPool<Component>();
		}
		return static_cast<ComponentPool<Component>*>(_pools[id]);
	}

	template <typename Component>
	[[nodiscard]] auto get_pool() const -> ComponentPool<Component>* {
		const auto it = _pools.find(get_component_id<Component>());
		if (it == _pools.end()) {
			return nullptr;
		}
		return static_cast<ComponentPool<Component>*>(it->second);
	}
};

} // namespace void_engine::ecs
