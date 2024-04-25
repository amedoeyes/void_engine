#ifndef VOID_ECS_POOL_HPP
#define VOID_ECS_POOL_HPP

#include <cstddef>

class Pool {
	public:
	Pool(const size_t& size);
	~Pool();

	public:
	void* get(const size_t& index) const;

	public:
	size_t _size;
	char* _data;
};

#endif	// !VOID_ECS_POOL_HPP
