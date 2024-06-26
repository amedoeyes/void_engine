#ifndef VOID_ENGINE_ECS_POOL_HPP
#define VOID_ENGINE_ECS_POOL_HPP

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/pool_base.hpp"

#include <cstddef>
#include <vector>

namespace void_engine::ECS {

template <typename T>
class Pool : public PoolBase {
public:
	~Pool() override {
		for (auto& ptr : _data) delete ptr;
	}

public:
	template <typename... Args>
	auto create(Entity entity, Args&&... args) -> T* {
		const EntityIndex index = get_entity_index(entity);

		if (index >= _sparse.size()) {
			_sparse.resize(index + 1, INVALID_ENTITY);
		}

		if (contains(entity)) {
			delete _data[_sparse[index]];
			_data[_sparse[index]] = new T{std::forward<Args>(args)...};
		}

		_sparse[index] = _packed.size();
		_packed.push_back(entity);
		_data.push_back(new T{std::forward<Args>(args)...});

		return _data.back();
	}

	void destroy(Entity entity) override {
		if (!contains(entity)) return;

		const EntityIndex index = get_entity_index(entity);
		const size_t remove_index = _sparse[index];
		Entity replacement = _packed.back();

		delete _data[remove_index];
		_data[remove_index] = _data.back();
		_data.pop_back();

		_packed[remove_index] = replacement;
		_packed.pop_back();

		_sparse[get_entity_index(replacement)] = remove_index;
		_sparse[index] = INVALID_ENTITY;
	}

	void clear() {
		for (auto& ptr : _data) delete ptr;
		_sparse.clear();
		_packed.clear();
		_data.clear();
	}

	auto get(Entity entity) -> T* {
		if (!contains(entity)) return nullptr;
		return _data[_sparse[get_entity_index(entity)]];
	}

	[[nodiscard]] auto contains(Entity entity) const -> bool {
		const EntityIndex index = get_entity_index(entity);
		if (index >= _sparse.size()) return false;
		return _sparse[index] != INVALID_ENTITY;
	}

	[[nodiscard]] auto get_entities() const
		-> const std::vector<Entity>& override {
		return _packed;
	}

private:
	std::vector<size_t> _sparse;
	std::vector<Entity> _packed;
	std::vector<T*> _data;
};

} // namespace void_engine::ECS

#endif // !VOID_ENGINE_ECS_POOL_HPP
