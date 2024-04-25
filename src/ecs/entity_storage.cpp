#include "ecs/entity_storage.hpp"

EntityID EntityStorage::create() {
	if (!_free.empty()) {
		EntityIndex index = _free.back();
		_free.pop_back();
		EntityID id = create_id(index, get_version(_data[index]) + 1);
		_data[index] = id;
		return id;
	}

	EntityID id = create_id(_data.size(), 0);
	_data.push_back(id);
	return id;
}

EntityID EntityStorage::get(const EntityIndex& index) const {
	if (index >= _data.size()) return invalid_id();
	return _data[index];
}

void EntityStorage::destroy(const EntityID& id) {
	EntityID new_id = create_id(invalid_index(), get_version(id));
	_data[get_index(id)] = new_id;
	_free.push_back(id);
}

size_t EntityStorage::size() const {
	return _data.size();
}

EntityIndex EntityStorage::get_index(const EntityID& id) const {
	return (EntityIndex)(id >> 32);
}

EntityVersion EntityStorage::get_version(const EntityID& id) const {
	return (EntityVersion)(id);
}

bool EntityStorage::is_valid(const EntityID& id) const {
	return get_index(id) != invalid_index();
}

bool EntityStorage::exists(const EntityID& id) const {
	return _data[get_index(id)] == id;
}

constexpr EntityID EntityStorage::invalid_id() {
	return EntityID(-1);
}

constexpr EntityIndex EntityStorage::invalid_index() {
	return EntityIndex(-1);
}

EntityID EntityStorage::create_id(
	const EntityIndex& index, const EntityVersion& version
) {
	return (static_cast<EntityID>(index) << 32) |
		   static_cast<EntityID>(version);
}
