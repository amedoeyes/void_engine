#ifndef VOID_ENGINE_UTILITY_GET_GL_TYPE_HPP
#define VOID_ENGINE_UTILITY_GET_GL_TYPE_HPP

#include <cassert>

namespace void_engine::utility {

template <typename T>
auto get_gl_type() -> unsigned int {
	assert(false && "Unsupported type");
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

#endif // VOID_ENGINE_UTILITY_GET_GL_TYPE_HPP
