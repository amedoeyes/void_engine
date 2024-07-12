#ifndef VOID_ENGINE_ECS_ENTITY_STORAGE_HPP
#define VOID_ENGINE_ECS_ENTITY_STORAGE_HPP

#include "void_engine/ecs/entity.hpp"

#include <queue>
#include <vector>

namespace void_engine::ecs {

class EntityManager {
public:
	EntityManager(const EntityManager&) = default;
	EntityManager(EntityManager&&) noexcept = default;
	auto operator=(const EntityManager&) -> EntityManager& = default;
	auto operator=(EntityManager&&) -> EntityManager& = default;
	EntityManager() = default;
	~EntityManager() = default;

	[[nodiscard]] auto create() -> Entity;
	void destroy(Entity entity);
	[[nodiscard]] auto contains(Entity entity) const -> bool;

private:
	std::vector<Entity> _data;
	std::queue<EntityIndex> _free;
};

} // namespace void_engine::ecs

#endif // !VOID_ENGINE_ECS_ENTITY_STORAGE_HPP
