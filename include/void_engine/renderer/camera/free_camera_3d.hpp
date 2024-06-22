#ifndef VOID_ENGINE_RENDERER_FREE_CAMERA_3D_HPP
#define VOID_ENGINE_RENDERER_FREE_CAMERA_3D_HPP

#include "void_engine/renderer/camera/perspective_camera.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>

namespace void_engine::renderer::camera {

class FreeCamera3D : public PerspectiveCamera {
public:
	FreeCamera3D();

public:
	void set_fov(float fov) override;
	void set_aspect(float aspect) override;
	void set_near_plane(float near_plane) override;
	void set_far_plane(float far_plane) override;
	void set_position(glm::vec3 position) override;
	void set_rotation(glm::vec3 rotation) override;
	void move(glm::vec3 movement) override;
	void rotate(glm::vec3 rotation) override;
	[[nodiscard]] auto get_fov() const -> float override;
	[[nodiscard]] auto get_aspect() const -> float override;
	[[nodiscard]] auto get_near_plane() const -> float override;
	[[nodiscard]] auto get_far_plane() const -> float override;
	[[nodiscard]] auto get_position() const -> glm::vec3 override;
	[[nodiscard]] auto get_rotation() const -> glm::vec3 override;
	[[nodiscard]] auto get_view() const -> glm::mat4 override;
	[[nodiscard]] auto get_projection() const -> glm::mat4 override;

private:
	glm::mat4 _view;
	glm::vec3 _position = glm::vec3(0.f);
	glm::quat _orientation = glm::quat(1.f, 0.f, 0.f, 0.f);

	glm::mat4 _projection;
	float _fov = glm::pi<float>() * .25;
	float _aspect;
	float _near_plane = 0.1f;
	float _far_plane = 1000.f;

private:
	void update_view();
	void update_projection();
	auto calculate_rotation(glm::vec3 rotation) -> glm::quat;
};

} // namespace void_engine::renderer::camera

#endif // !VOID_ENGINE_RENDERER_FREE_CAMERA_3D_HPP
