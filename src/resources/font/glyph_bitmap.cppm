export module void_engine.resources:glyph_bitmap;

import std;
import glm;

export namespace void_engine::resources {

struct GlyphBitmap {
	std::vector<std::byte> buffer;
	glm::ivec2 size;
	glm::ivec2 bearing;
};

} // namespace void_engine::resources
