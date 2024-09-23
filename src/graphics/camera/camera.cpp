#include "void_engine/graphics/camera/camera.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

namespace void_engine::graphics::camera {

void Camera::set_near_plane(float near_plane) {
	_near_plane = near_plane;
	update_projection();
}

void Camera::set_far_plane(float far_plane) {
	_far_plane = far_plane;
	update_projection();
}

void Camera::set_position(const glm::vec3& position) {
	_position = position;
	update_view();
}

void Camera::set_rotation(const glm::vec3& rotation) {
	_orientation = glm::normalize(calculate_rotation(rotation));
	update_view();
}

void Camera::move(const glm::vec3& movement) {
	_position += _orientation * movement;
	update_view();
}

void Camera::rotate(glm::vec3 rotation) {
	_orientation = glm::normalize(calculate_rotation(rotation) * _orientation);
	update_view();
}

auto Camera::is_in_frustum(const glm::vec3& point) const -> bool {
	const glm::vec4 clip = _view_projection * glm::vec4(point, 1.0f);
	if (clip.x < -clip.w || clip.x > clip.w) {
		return false;
	}
	if (clip.y < -clip.w || clip.y > clip.w) {
		return false;
	}
	if (clip.z < -clip.w || clip.z > clip.w) {
		return false;
	}
	return true;
}

auto Camera::get_near_plane() const -> float {
	return _near_plane;
}

auto Camera::get_far_plane() const -> float {
	return _far_plane;
}

auto Camera::get_position() const -> const glm::vec3& {
	return _position;
}

auto Camera::get_rotation() const -> glm::vec3 {
	return glm::eulerAngles(_orientation);
}

auto Camera::get_view() const -> const glm::mat4& {
	return _view;
}

auto Camera::get_projection() const -> const glm::mat4& {
	return _projection;
}

auto Camera::get_view_projection() const -> const glm::mat4& {
	return _view_projection;
}

void Camera::update_view() {
	_view = glm::translate(glm::mat4_cast(glm::conjugate(_orientation)), -_position);
	update_view_projection();
}

void Camera::update_view_projection() {
	_view_projection = _projection * _view;
}

auto Camera::calculate_rotation(const glm::vec3& rotation) -> glm::quat {
	const glm::quat x = glm::angleAxis(rotation.x, _orientation * glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::quat y = glm::angleAxis(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::quat z = glm::angleAxis(rotation.z, _orientation * glm::vec3(0.0f, 0.0f, -1.0f));
	return y * x * z;
}

} // namespace void_engine::graphics::camera
