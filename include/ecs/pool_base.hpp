#ifndef VOID_ECS_POOL_BASE_HPP
#define VOID_ECS_POOL_BASE_HPP

#include <vector>

#include "ecs/common.hpp"

namespace Void::ECS {

class PoolBase {
	public:
	virtual ~PoolBase() = default;
	virtual void destroy(const Entity& entity) = 0;
	virtual const std::vector<Entity>& get_entities() const = 0;
};

}  // namespace Void::ECS

#endif	// !VOID_ECS_POOL_BASE_HPP
