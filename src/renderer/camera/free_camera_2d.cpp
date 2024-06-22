#include "void_engine/renderer/camera/free_camera_2d.hpp"

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

FreeCamera2D::FreeCamera2D() {
	const glm::vec2 viewport = Renderer::get_viewport_size();
	_left = -viewport.x / 2.f;
	_right = viewport.x / 2.f;
	_bottom = -viewport.y / 2.f;
	_top = viewport.y / 2.f;
	update_view();
	update_projection();
}

void FreeCamera2D::set_left(float left) {
	_left = left;
	update_projection();
}

void FreeCamera2D::set_right(float right) {
	_right = right;
	update_projection();
}

void FreeCamera2D::set_bottom(float bottom) {
	_bottom = bottom;
	update_projection();
}

void FreeCamera2D::set_top(float top) {
	_top = top;
	update_projection();
}

void FreeCamera2D::set_dimensions(
	float left, float right, float bottom, float top
) {
	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;
	update_projection();
}

void FreeCamera2D::set_dimensions(glm::vec2 dimensions) {
	_left = -dimensions.x / 2.f;
	_right = dimensions.x / 2.f;
	_bottom = -dimensions.y / 2.f;
	_top = dimensions.y / 2.f;
	update_projection();
}

void FreeCamera2D::set_near_plane(float near_plane) {
	_near_plane = near_plane;
	update_projection();
}

void FreeCamera2D::set_far_plane(float far_plane) {
	_far_plane = far_plane;
	update_projection();
}

void FreeCamera2D::set_position(glm::vec3 position) {
	_position = position;
	update_view();
}

void FreeCamera2D::set_rotation(glm::vec3 rotation) {
	_orientation = glm::normalize(calculate_rotation(rotation));
	update_view();
}

void FreeCamera2D::set_zoom(float zoom) {
	_zoom = zoom;
	update_projection();
}

void FreeCamera2D::zoom(float zoom) {
	_zoom *= zoom;
	update_projection();
}

void FreeCamera2D::move(glm::vec3 movement) {
	_position += _orientation * movement;
	update_view();
}

void FreeCamera2D::rotate(glm::vec3 rotation) {
	_orientation = glm::normalize(calculate_rotation(rotation) * _orientation);
	update_view();
}

auto FreeCamera2D::get_left() const -> float {
	return _left;
}

auto FreeCamera2D::get_right() const -> float {
	return _right;
}

auto FreeCamera2D::get_bottom() const -> float {
	return _bottom;
}

auto FreeCamera2D::get_top() const -> float {
	return _top;
}

auto FreeCamera2D::get_near_plane() const -> float {
	return _near_plane;
}

auto FreeCamera2D::get_far_plane() const -> float {
	return _far_plane;
}

auto FreeCamera2D::get_position() const -> glm::vec3 {
	return _position;
}

auto FreeCamera2D::get_rotation() const -> glm::vec3 {
	return glm::eulerAngles(_orientation);
}

auto FreeCamera2D::get_view() const -> glm::mat4 {
	return _view;
}

auto FreeCamera2D::get_zoom() const -> float {
	return _zoom;
}

auto FreeCamera2D::get_projection() const -> glm::mat4 {
	return _projection;
}

void FreeCamera2D::update_view() {
	_view = glm::translate(
		glm::mat4_cast(glm::conjugate(_orientation)), -_position
	);
}

void FreeCamera2D::update_projection() {
	_projection = glm::ortho(
		_left * _zoom, _right * _zoom, _bottom * _zoom, _top * _zoom,
		_near_plane, _far_plane
	);
}

auto FreeCamera2D::calculate_rotation(glm::vec3 rotation) -> glm::quat {
	const glm::quat x =
		glm::angleAxis(rotation.x, _orientation * glm::vec3(1, 0, 0));
	const glm::quat y = glm::angleAxis(rotation.y, glm::vec3(0, 1, 0));
	const glm::quat z =
		glm::angleAxis(rotation.z, _orientation * glm::vec3(0, 0, -1));
	return y * x * z;
}

} // namespace void_engine::renderer::camera
