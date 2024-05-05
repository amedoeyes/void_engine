#ifndef VOID_ENGINE_ECS_ENTITY_STORAGE_HPP
#define VOID_ENGINE_ECS_ENTITY_STORAGE_HPP

#include <vector>

#include "void_engine/ecs/common.hpp"

namespace void_engine::ECS {

class EntityStorage {
	public:
	Entity create();
	void destroy(const Entity& id);
	Entity get(const EntityIndex& index) const;
	bool contains(const Entity& id) const;

	private:
	std::vector<Entity> _data;
	std::vector<EntityIndex> _free;
};

}  // namespace void_engine::ECS

#endif	// !VOID_ENGINE_ECS_ENTITY_STORAGE_HPP
