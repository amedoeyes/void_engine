#ifndef VOID_ENGINE_ECS_POOL_BASE_HPP
#define VOID_ENGINE_ECS_POOL_BASE_HPP

#include "void_engine/ecs/common.hpp"

#include <vector>

namespace void_engine::ECS {

class PoolBase {
public:
	virtual ~PoolBase() = default;
	virtual void destroy(Entity entity) = 0;
	[[nodiscard]] virtual auto get_entities() const
		-> const std::vector<Entity>& = 0;
};

} // namespace void_engine::ECS

#endif // !VOID_ENGINE_ECS_POOL_BASE_HPP
