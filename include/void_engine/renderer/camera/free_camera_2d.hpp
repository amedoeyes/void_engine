#ifndef VOID_ENGINE_RENDERER_FREE_CAMERA_2D_HPP
#define VOID_ENGINE_RENDERER_FREE_CAMERA_2D_HPP

#include "void_engine/renderer/camera/orthographic_camera.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

namespace void_engine::renderer::camera {

class FreeCamera2D : public OrthographicCamera {
public:
	FreeCamera2D();

public:
	void set_left(float left) override;
	void set_right(float right) override;
	void set_bottom(float bottom) override;
	void set_top(float top) override;
	void set_dimensions(float left, float right, float bottom, float top)
		override;
	void set_dimensions(glm::vec2 dimensions) override;
	void set_near_plane(float near_plane) override;
	void set_far_plane(float far_plane) override;
	void set_position(glm::vec3 position) override;
	void set_rotation(glm::vec3 rotation) override;
	void set_zoom(float zoom) override;
	void zoom(float zoom) override;
	void move(glm::vec3 movement) override;
	void rotate(glm::vec3 rotation) override;
	[[nodiscard]] auto get_left() const -> float override;
	[[nodiscard]] auto get_right() const -> float override;
	[[nodiscard]] auto get_bottom() const -> float override;
	[[nodiscard]] auto get_top() const -> float override;
	[[nodiscard]] auto get_near_plane() const -> float override;
	[[nodiscard]] auto get_far_plane() const -> float override;
	[[nodiscard]] auto get_position() const -> glm::vec3 override;
	[[nodiscard]] auto get_rotation() const -> glm::vec3 override;
	[[nodiscard]] auto get_view() const -> glm::mat4 override;
	[[nodiscard]] auto get_zoom() const -> float override;
	[[nodiscard]] auto get_projection() const -> glm::mat4 override;

private:
	glm::mat4 _view;
	glm::vec3 _position = glm::vec3(0.f);
	glm::quat _orientation = glm::quat(1.f, 0.f, 0.f, 0.f);

	glm::mat4 _projection;
	float _left;
	float _right;
	float _bottom;
	float _top;
	float _near_plane = 0.1f;
	float _far_plane = 1000.f;
	float _zoom = 1.f;

private:
	void update_view();
	void update_projection();
	auto calculate_rotation(glm::vec3 rotation) -> glm::quat;
};

} // namespace void_engine::renderer::camera

#endif // !VOID_ENGINE_RENDERER_FREE_CAMERA_2D_HPP
