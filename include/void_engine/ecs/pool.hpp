#ifndef VOID_ENGINE_ECS_POOL_HPP
#define VOID_ENGINE_ECS_POOL_HPP

#include <vector>

#include "void_engine/ecs/common.hpp"
#include "void_engine/ecs/pool_base.hpp"

namespace void_engine::ECS {

template <typename T>
class Pool : public PoolBase {
	public:
	~Pool() {
		for (auto& ptr : _data) delete ptr;
	}

	public:
	template <typename... Args>
	T* create(const Entity& entity, Args&&... args) {
		EntityIndex index = get_entity_index(entity);

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

	void destroy(const Entity& entity) {
		if (!contains(entity)) return;

		EntityIndex index = get_entity_index(entity);
		size_t remove_index = _sparse[index];
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

	T* get(const Entity& entity) {
		if (!contains(entity)) return nullptr;
		return _data[_sparse[get_entity_index(entity)]];
	}

	bool contains(const Entity& entity) const {
		EntityIndex index = get_entity_index(entity);
		if (index >= _sparse.size()) return false;
		return _sparse[index] != INVALID_ENTITY;
	}

	const std::vector<Entity>& get_entities() const {
		return _packed;
	}

	public:
	std::vector<size_t> _sparse;
	std::vector<Entity> _packed;
	std::vector<T*> _data;
};

}  // namespace void_engine::ECS

#endif	// !VOID_ENGINE_ECS_POOL_HPP
