#ifndef VOID_ECS_ENTITY_STORAGE_HPP
#define VOID_ECS_ENTITY_STORAGE_HPP

#include <vector>

#include "ecs/common.hpp"

namespace Void::ECS {

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

}  // namespace Void::ECS

#endif	// !VOID_ECS_ENTITY_STORAGE_HPP
