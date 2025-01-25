module;

#include <glad/glad.h>

module void_engine.utility.get_gl_type;

namespace void_engine::utility {

template <>
auto get_gl_type<float>() -> unsigned int {
	return GL_FLOAT;
}

template <>
auto get_gl_type<int>() -> unsigned int {
	return GL_INT;
}

template <>
auto get_gl_type<unsigned int>() -> unsigned int {
	return GL_UNSIGNED_INT;
}

template <>
auto get_gl_type<unsigned char>() -> unsigned int {
	return GL_UNSIGNED_BYTE;
}

} // namespace void_engine::utility
