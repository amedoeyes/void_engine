#ifndef VOID_ENGINE_GRAPHICS_CAMERA_ENUMS_HPP
#define VOID_ENGINE_GRAPHICS_CAMERA_ENUMS_HPP

#include <cstdint>

namespace void_engine::graphics::camera {

enum class Type : uint8_t {
	orthographic,
	perspective
};

} // namespace void_engine::graphics::camera

#endif // VOID_ENGINE_GRAPHICS_CAMERA_ENUMS_HPP
