#ifndef VOID_ENGINE_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP
#define VOID_ENGINE_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP

#include "glm/ext/vector_float2.hpp"
#include "void_engine/renderer/camera/camera.hpp"

namespace void_engine::renderer::camera {

class OrthographicCamera : public Camera {
public:
	virtual void set_left(float left) = 0;
	virtual void set_right(float right) = 0;
	virtual void set_bottom(float bottom) = 0;
	virtual void set_top(float top) = 0;
	virtual void set_dimensions(
		float left, float right, float bottom, float top
	) = 0;
	virtual void set_dimensions(glm::vec2 dimensions) = 0;
	virtual void set_zoom(float zoom) = 0;
	virtual void zoom(float zoom) = 0;
	[[nodiscard]] virtual auto get_left() const -> float = 0;
	[[nodiscard]] virtual auto get_right() const -> float = 0;
	[[nodiscard]] virtual auto get_bottom() const -> float = 0;
	[[nodiscard]] virtual auto get_top() const -> float = 0;
	[[nodiscard]] virtual auto get_zoom() const -> float = 0;
	[[nodiscard]] auto get_type() const -> CameraType override {
		return CameraType::orthographic;
	}
};

} // namespace void_engine::renderer::camera

#endif // !VOID_ENGINE_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP
