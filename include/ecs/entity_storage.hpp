#ifndef VOID_ECS_ENTITY_STORAGE_HPP
#define VOID_ECS_ENTITY_STORAGE_HPP

#include <vector>

#include "ecs/common.hpp"

class EntityStorage {
	public:
	EntityID create();
	EntityID get(const EntityIndex& index) const;
	void destroy(const EntityID& id);
	size_t size() const;
	EntityIndex get_index(const EntityID& id) const;
	EntityVersion get_version(const EntityID& id) const;
	bool is_valid(const EntityID& id) const;
	bool exists(const EntityID& id) const;

	private:
	std::vector<EntityID> _data;
	std::vector<EntityID> _free;

	private:
	static constexpr EntityID invalid_id();
	static constexpr EntityIndex invalid_index();
	EntityID create_id(const EntityIndex& index, const EntityVersion& version);
};

#endif	// !VOID_ECS_ENTITY_STORAGE_HPP
