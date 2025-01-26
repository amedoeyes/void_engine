export module void_engine.resources:image.enums;

import std;

namespace void_engine::resource::image {

enum class ColorType : std::uint8_t {
	none,
	gray,
	gray_alpha,
	rgb,
	rgba,
};

} // namespace void_engine::resource::image
