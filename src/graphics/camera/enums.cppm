export module void_engine.graphics:camera.enums;

import std;

export namespace void_engine::graphics::camera {

enum class Type : std::uint8_t {
	orthographic,
	perspective
};

} // namespace void_engine::graphics::camera
