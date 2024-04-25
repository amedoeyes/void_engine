#ifndef VOID_ECS_SCENE_VIEW_HPP
#define VOID_ECS_SCENE_VIEW_HPP

#include "ecs/scene.hpp"

namespace Void::ECS {

template <typename... Components>
class SceneView {
	public:
	SceneView(const Scene& scene) : _scene(&scene) {
		if constexpr (sizeof...(Components) == 0) {
			_all = true;
		} else {
			(_mask.set(get_component_id<Components>()), ...);
		}
	}

	public:
	class Iterator {
		public:
		Iterator(
			const Scene& scene, const EntityIndex& index, Mask mask, bool all
		)
			: _scene(&scene), _index(index), _mask(mask), _all(all) {}

		public:
		Entity operator*() const {
			return _scene->_entities.get(_index);
		}

		bool operator==(const Iterator& other) const {
			return _index == other._index;
		}

		bool operator!=(const Iterator& other) const {
			return _index != other._index;
		}

		Iterator& operator++() {
			do {
				_index++;
			} while (_index < _scene->_entities.size() &&
					 !is_valid(_scene, _index, _mask, _all));
			return *this;
		}

		private:
		const Scene* _scene;
		EntityIndex _index;
		Mask _mask;
		bool _all;
	};

	const Iterator begin() const {
		EntityIndex index = 0;
		while (index < _scene->_entities.size() &&
			   !is_valid(_scene, index, _mask, _all)) {
			index++;
		}
		return Iterator(*_scene, index, _mask, _all);
	}

	const Iterator end() const {
		return Iterator(*_scene, _scene->_entities.size(), _mask, _all);
	}

	private:
	const Scene* _scene;
	Mask _mask;
	bool _all = false;

	private:
	static bool is_valid(
		const Scene* scene, EntityIndex index, Mask mask, bool all
	) {
		EntityID id = scene->_entities.get(index);
		bool is_valid_entity = scene->_entities.is_valid(id);
		Mask entity_mask = scene->_masks[index];
		return is_valid_entity && (all || mask == (mask & entity_mask));
	}
};

}  // namespace Void::ECS

#endif	//! VOID_ECS_SCENE_VIEW_HPP
