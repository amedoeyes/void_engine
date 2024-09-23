#ifndef VOID_ENGINE_GRAPHICS_CAMERA_ORTHOGRAPHIC_CAMERA_HPP
#define VOID_ENGINE_GRAPHICS_CAMERA_ORTHOGRAPHIC_CAMERA_HPP

#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/graphics/camera/enums.hpp"

#include <glm/ext/vector_float2.hpp>

namespace void_engine::graphics::camera {

class OrthographicCamera : public Camera {
public:
	void set_left(float left);
	void set_right(float right);
	void set_bottom(float bottom);
	void set_top(float top);
	void set_dimensions(float left, float right, float bottom, float top);
	void set_dimensions(const glm::vec2& dimensions);
	void set_zoom(float zoom);
	void zoom(float zoom);
	void set_size(const glm::vec2& size) override;
	[[nodiscard]] auto get_left() const -> float;
	[[nodiscard]] auto get_right() const -> float;
	[[nodiscard]] auto get_bottom() const -> float;
	[[nodiscard]] auto get_top() const -> float;
	[[nodiscard]] auto get_zoom() const -> float;
	[[nodiscard]] auto get_type() const -> Type override;

protected:
	float _zoom = 1.0f;
	float _left = 0.0f;
	float _right = 0.0f;
	float _bottom = 0.0f;
	float _top = 0.0f;

	void update_projection() override;
};

} // namespace void_engine::graphics::camera

#endif // !VOID_ENGINE_GRAPHICS_CAMERA_ORTHOGRAPHIC_CAMERA_HPP
