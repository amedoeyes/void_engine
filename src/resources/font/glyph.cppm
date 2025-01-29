export module void_engine.resources:glyph;

import std;
import glm;

export namespace void_engine::resources {

struct Glyph {
	std::uint32_t codepoint;
	glm::vec2 offset;
	glm::vec2 advance;
};

} // namespace void_engine::resources
