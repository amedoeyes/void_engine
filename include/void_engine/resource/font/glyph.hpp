#ifndef VOID_ENGINE_RESOURCE_FONT_GLYPH_HPP
#define VOID_ENGINE_RESOURCE_FONT_GLYPH_HPP

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_uint2.hpp>

namespace void_engine::resource::font {

struct Glyph {
	unsigned int codepoint;
	glm::uvec2 size;
	glm::ivec2 bearing;
	glm::vec2 advance;
	glm::vec2 uv_position;
	glm::vec2 uv_size;
};

} // namespace void_engine::resource::font

#endif // VOID_ENGINE_RESOURCE_FONT_GLYPH_HPP
