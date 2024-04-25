#include "ecs/pool.hpp"

#include "ecs/common.hpp"

Pool::Pool(const size_t& size)
	: _size(size), _data(new char[size * MAX_ENTITIES]) {}

Pool::~Pool() {
	delete[] _data;
}

void* Pool::get(const size_t& index) const {
	return &_data[index * _size];
}
