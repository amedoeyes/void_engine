export module void_engine.ecs:component_pool.base;

import :entity;

import std;

export namespace void_engine::ecs {

class ComponentPoolBase {
public:
	ComponentPoolBase(const ComponentPoolBase&) = default;
	ComponentPoolBase(ComponentPoolBase&&) = delete;
	auto operator=(const ComponentPoolBase&) -> ComponentPoolBase& = default;
	auto operator=(ComponentPoolBase&&) -> ComponentPoolBase& = delete;
	ComponentPoolBase() = default;
	virtual ~ComponentPoolBase() = default;
	virtual void destroy(Entity entity) = 0;
	[[nodiscard]]
	virtual auto contains(Entity entity) const -> bool
		= 0;
	[[nodiscard]]
	virtual auto get_entities() const -> const std::vector<Entity>& = 0;
};

} // namespace void_engine::ecs
