module;

#include <cassert>

export module void_engine.ecs:world;

import :component_pool.manager;
import :entity;
import :entity.manager;

import std;

export namespace void_engine::ecs {

class World {
public:
	World(const World&) = default;
	World(World&&) = delete;
	auto operator=(const World&) -> World& = default;
	auto operator=(World&&) -> World& = delete;
	World() = default;
	~World() = default;

	auto create() -> Entity { return _entities.create(); }

	template<typename... Components>
	auto create() -> Entity {
		const Entity entity = create();
		(_pools.create<Components>(entity), ...);
		return entity;
	}

	template<typename... Components>
	auto create(Components&&... component) -> Entity {
		const Entity entity = create();
		(_pools.create(entity, std::forward<Components>(component)), ...);
		return entity;
	}

	void destroy(Entity entity) {
		assert(contains(entity) && "Entity does not exist");
		_pools.destroy(entity);
		_entities.destroy(entity);
	}

	[[nodiscard]]
	auto contains(Entity entity) const -> bool {
		return _entities.contains(entity);
	}

	template<typename Component>
	auto attach(Entity entity) -> Component& {
		assert(contains(entity) && "Entity does not exist");
		return _pools.create<Component>(entity);
	}

	template<typename Component>
	auto attach(Entity entity, Component&& component) -> Component& {
		assert(contains(entity) && "Entity does not exist");
		return _pools.create(entity, std::forward<Component>(component));
	}

	template<typename... Components>
		requires(sizeof...(Components) > 1)
	auto attach(Entity entity) -> std::tuple<Components&...> {
		assert(contains(entity) && "Entity does not exist");
		return {_pools.create<Components>(entity)...};
	}

	template<typename... Components>
		requires(sizeof...(Components) > 1)
	auto attach(Entity entity, Components&&... components) -> std::tuple<Components&...> {
		assert(contains(entity) && "Entity does not exist");
		return {_pools.create(entity, std::forward<Components>(components))...};
	}

	template<typename Component>
	void detach(Entity entity) {
		assert(contains(entity) && "Entity does not exist");
		_pools.destroy<Component>(entity);
	}

	template<typename... Components>
		requires(sizeof...(Components) > 1)
	void detach(Entity entity) {
		assert(contains(entity) && "Entity does not exist");
		(_pools.destroy<Components>(entity), ...);
	}

	template<typename Component>
	[[nodiscard]]
	auto fetch(Entity entity) -> Component& {
		assert(contains(entity) && "Entity does not exist");
		return _pools.get<Component>(entity);
	}

	template<typename... Components>
		requires(sizeof...(Components) > 1)
	[[nodiscard]]
	auto fetch(Entity entity) -> std::tuple<Components&...> {
		assert(contains(entity) && "Entity does not exist");
		return {_pools.get<Components>(entity)...};
	}

	template<typename Component>
	[[nodiscard]]
	auto has(Entity entity) const -> bool {
		assert(contains(entity) && "Entity does not exist");
		return _pools.contains<Component>(entity);
	}

	template<typename... Components>
		requires(sizeof...(Components) > 1)
	[[nodiscard]]
	auto has(Entity entity) const -> bool {
		assert(contains(entity) && "Entity does not exist");
		return (_pools.contains<Components>(entity) && ...);
	}

	[[nodiscard]]
	auto query() const -> std::vector<Entity> {
		return _pools.query();
	}

	template<typename Component>
	[[nodiscard]]
	auto query() const -> const std::vector<Entity>& {
		return _pools.query<Component>();
	}

	template<typename... Components>
		requires(sizeof...(Components) > 1)
	[[nodiscard]]
	auto query() const -> std::vector<Entity> {
		return _pools.query<Components...>();
	}

private:
	EntityManager _entities;
	ComponentPoolManager _pools;
};

} // namespace void_engine::ecs
