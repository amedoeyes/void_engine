module;

#include <cassert>

export module void_engine.ecs:component_pool;

import :component_pool.base;
import :entity;

import std;

export namespace void_engine::ecs {

constexpr auto invalid_index = std::size_t(-1);

template<typename Component>
class ComponentPool : public ComponentPoolBase {
public:
	ComponentPool(const ComponentPool&) = delete;
	ComponentPool(ComponentPool&&) = delete;
	auto operator=(const ComponentPool&) -> ComponentPool& = delete;
	auto operator=(ComponentPool&&) -> ComponentPool& = delete;
	ComponentPool() = default;

	~ComponentPool() override {
		for (const auto* component : _data) {
			delete component;
		}
	}

	auto create(Entity entity) -> Component& {
		const EntityIndex index = get_entity_index(entity);
		if (index >= _sparse.size()) {
			_sparse.resize(index + 1, invalid_index);
		}
		if (_sparse[index] == invalid_index) {
			_sparse[index] = _packed.size();
			_packed.push_back(entity);
			_data.push_back(new Component());
		}
		return *(_data[_sparse[index]]);
	}

	auto create(Entity entity, Component&& component) -> Component& {
		const EntityIndex index = get_entity_index(entity);
		if (index >= _sparse.size()) {
			_sparse.resize(index + 1, invalid_index);
		}
		if (_sparse[index] == invalid_index) {
			_sparse[index] = _packed.size();
			_packed.push_back(entity);
			_data.push_back(new Component(std::move(component)));
		} else {
			new (_data[_sparse[index]]) Component(std::move(component));
		}
		return *(_data[_sparse[index]]);
	}

	void destroy(Entity entity) override {
		assert(contains(entity) && "Entity does not exist");

		const EntityIndex index = get_entity_index(entity);
		const std::size_t remove_index = _sparse[index];
		Entity replacement = _packed.back();

		delete _data[remove_index];
		_data[remove_index] = _data.back();
		_data.pop_back();

		_packed[remove_index] = replacement;
		_packed.pop_back();

		_sparse[get_entity_index(replacement)] = remove_index;
		_sparse[index] = invalid_index;
	}

	void clear() {
		for (const auto* component : _data) {
			delete component;
		}
		_sparse.clear();
		_packed.clear();
		_data.clear();
	}

	auto get(Entity entity) -> Component& {
		assert(contains(entity) && "Entity does not exist");
		return *(_data[_sparse[get_entity_index(entity)]]);
	}

	[[nodiscard]]
	auto contains(Entity entity) const -> bool override {
		const EntityIndex index = get_entity_index(entity);
		if (index >= _sparse.size()) {
			return false;
		}
		return _sparse[index] != invalid_index;
	}

	[[nodiscard]]
	auto get_entities() const -> const std::vector<Entity>& override {
		return _packed;
	}

private:
	std::vector<std::size_t> _sparse;
	std::vector<Entity> _packed;
	std::vector<Component*> _data;
};

} // namespace void_engine::ecs
