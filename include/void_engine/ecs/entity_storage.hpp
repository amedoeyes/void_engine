#ifndef VOID_ENGINE_ECS_ENTITY_STORAGE_HPP
#define VOID_ENGINE_ECS_ENTITY_STORAGE_HPP

#include "void_engine/ecs/common.hpp"

#include <vector>

namespace void_engine::ECS {

class EntityStorage {
public:
	auto create() -> Entity;
	void destroy(Entity id);
	[[nodiscard]] auto get(EntityIndex index) const -> Entity;
	[[nodiscard]] auto contains(Entity id) const -> bool;

private:
	std::vector<Entity> _data;
	std::vector<EntityIndex> _free;
};

} // namespace void_engine::ECS

#endif // !VOID_ENGINE_ECS_ENTITY_STORAGE_HPP
