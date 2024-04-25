#ifndef VOID_ECS_SCENE_HPP
#define VOID_ECS_SCENE_HPP

#include "ecs/common.hpp"
#include "ecs/entity_storage.hpp"
#include "ecs/pool.hpp"

namespace Void::ECS {

class Scene {
	template <typename... Components>
	friend class SceneView;

	public:
	Scene() = default;
	~Scene();

	public:
	Entity create();
	void destroy(const Entity& id);

	template <typename T, typename... Args>
	T* add(const Entity& id, Args&&... args) {
		if (!_entities.exists(id)) return nullptr;

		ComponentID component_id = get_component_id<T>();

		if (component_id >= _pools.size()) {
			_pools.resize(component_id + 1, nullptr);
		}

		if (_pools[component_id] == nullptr) {
			_pools[component_id] = new Pool(sizeof(T));
		}

		EntityIndex index = _entities.get_index(id);

		_masks[index].set(component_id);

		return new (_pools[component_id]->get(index))
			T{std::forward<Args>(args)...};
	}

	template <typename T>
	T* get(const Entity& id) {
		if (!_entities.exists(id)) return nullptr;

		EntityIndex index = _entities.get_index(id);
		ComponentID component_id = get_component_id<T>();

		if (!_masks[index].test(component_id)) return nullptr;

		return reinterpret_cast<T*>(_pools[component_id]->get(index));
	}

	private:
	EntityStorage _entities;
	std::vector<Mask> _masks;
	std::vector<Pool*> _pools;
};

}  // namespace Void::ECS

#endif	//! VOID_ECS_SCENE_HPP
