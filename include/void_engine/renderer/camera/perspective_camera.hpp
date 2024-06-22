#ifndef VOID_ENGINE_RENDERER_CAMERA_PERSPECTIVE_CAMERA_HPP
#define VOID_ENGINE_RENDERER_CAMERA_PERSPECTIVE_CAMERA_HPP

#include "void_engine/renderer/camera/camera.hpp"

namespace void_engine::renderer::camera {

class PerspectiveCamera : public Camera {
public:
	virtual void set_fov(float fov) = 0;
	virtual void set_aspect(float aspect) = 0;
	[[nodiscard]] virtual auto get_fov() const -> float = 0;
	[[nodiscard]] virtual auto get_aspect() const -> float = 0;
	[[nodiscard]] auto get_type() const -> CameraType override {
		return CameraType::perspective;
	}
};

} // namespace void_engine::renderer::camera

#endif // !VOID_ENGINE_RENDERER_CAMERA_PERSPECTIVE_CAMERA_HPP
