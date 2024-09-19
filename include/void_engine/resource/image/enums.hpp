#ifndef VOID_ENGINE_RESOURCE_IMAGE_ENUMS_HPP
#define VOID_ENGINE_RESOURCE_IMAGE_ENUMS_HPP

#include <cstdint>

namespace void_engine::resource::image {

enum class ColorType : uint8_t {
	none,
	gray,
	gray_alpha,
	rgb,
	rgba,
};

} // namespace void_engine::resource::image

#endif // !VOID_ENGINE_RESOURCE_IMAGE_ENUMS_HPP
