module;

#include <cassert>

export module void_engine.utility.get_gl_type;

export namespace void_engine::utility {

template <typename T>
auto get_gl_type() -> unsigned int {
	assert(false && "Unsupported type");
	return 0;
}

template <>
auto get_gl_type<float>() -> unsigned int;

template <>
auto get_gl_type<int>() -> unsigned int;

template <>
auto get_gl_type<unsigned int>() -> unsigned int;

template <>
auto get_gl_type<unsigned char>() -> unsigned int;

} // namespace void_engine::utility
