#include "void_engine/renderer/camera/free_camera_3d.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "void_engine/renderer/renderer.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace void_engine::renderer::camera {

FreeCamera3D::FreeCamera3D() {
	const glm::vec2 viewport = Renderer::get_viewport_size();
	_aspect = viewport.x / viewport.y;
	update_view();
	update_projection();
}

void FreeCamera3D::set_fov(float fov) {
	_fov = fov;
	update_projection();
}

void FreeCamera3D::set_aspect(float aspect) {
	_aspect = aspect;
	update_projection();
}

void FreeCamera3D::set_near_plane(float near_plane) {
	_near_plane = near_plane;
	update_projection();
}

void FreeCamera3D::set_far_plane(float far_plane) {
	_far_plane = far_plane;
	update_projection();
}

void FreeCamera3D::set_position(glm::vec3 position) {
	_position = position;
	update_view();
}

void FreeCamera3D::set_rotation(glm::vec3 rotation) {
	_orientation = glm::normalize(calculate_rotation(rotation));
	update_view();
}

void FreeCamera3D::move(glm::vec3 movement) {
	_position += _orientation * movement;
	update_view();
}

void FreeCamera3D::rotate(glm::vec3 rotation) {
	_orientation = glm::normalize(calculate_rotation(rotation) * _orientation);
	update_view();
}

auto FreeCamera3D::get_fov() const -> float {
	return _fov;
}

auto FreeCamera3D::get_aspect() const -> float {
	return _aspect;
}

auto FreeCamera3D::get_near_plane() const -> float {
	return _near_plane;
}

auto FreeCamera3D::get_far_plane() const -> float {
	return _far_plane;
}

auto FreeCamera3D::get_position() const -> glm::vec3 {
	return _position;
}

auto FreeCamera3D::get_rotation() const -> glm::vec3 {
	return glm::eulerAngles(_orientation);
}

auto FreeCamera3D::get_view() const -> glm::mat4 {
	return _view;
}

auto FreeCamera3D::get_projection() const -> glm::mat4 {
	return _projection;
}

void FreeCamera3D::update_view() {
	_view = glm::translate(
		glm::mat4_cast(glm::conjugate(_orientation)), -_position
	);
}

void FreeCamera3D::update_projection() {
	_projection = glm::perspective(_fov, _aspect, _near_plane, _far_plane);
}

auto FreeCamera3D::calculate_rotation(glm::vec3 rotation) -> glm::quat {
	const glm::quat x =
		glm::angleAxis(rotation.x, _orientation * glm::vec3(1, 0, 0));
	const glm::quat y = glm::angleAxis(rotation.y, glm::vec3(0, 1, 0));
	const glm::quat z =
		glm::angleAxis(rotation.z, _orientation * glm::vec3(0, 0, -1));
	return y * x * z;
}

} // namespace void_engine::renderer::camera
