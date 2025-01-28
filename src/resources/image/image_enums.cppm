export module void_engine.resources:image_enums;

import std;

export namespace void_engine::resources {

enum class ColorType : std::uint8_t {
	none,
	gray,
	gray_alpha,
	rgb,
	rgba,
};

} // namespace void_engine::resources
