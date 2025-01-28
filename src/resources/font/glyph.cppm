export module void_engine.resources:glyph;

import glm;

export namespace void_engine::resources {

struct Glyph {
	unsigned int codepoint;
	glm::uvec2 size;
	glm::ivec2 bearing;
	glm::vec2 advance;
	glm::vec2 uv_position;
	glm::vec2 uv_size;
};

} // namespace void_engine::resources
