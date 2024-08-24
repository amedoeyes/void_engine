#include "void_engine/utility/transform.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

namespace void_engine::utility {

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
	_position(position),
	_rotation(rotation),
	_scale(scale) {
}

void Transform::translate(const glm::vec3& translation) {
	_position += translation;
}

void Transform::rotate(float angle, const glm::vec3& axis) {
	_rotation = glm::angleAxis(angle, axis) * _rotation;
}

void Transform::rotate(const glm::vec3& rotation) {
	_rotation = glm::quat(rotation) * _rotation;
}

void Transform::scale(const glm::vec3& scale) {
	_scale *= scale;
}

void Transform::set_position(const glm::vec3& position) {
	_position = position;
}

void Transform::set_rotation(float angle, const glm::vec3& axis) {
	_rotation = glm::angleAxis(angle, axis);
}

void Transform::set_rotation(const glm::vec3& rotation) {
	_rotation = glm::quat(rotation);
}

void Transform::set_scale(const glm::vec3& scale) {
	_scale = scale;
}

auto Transform::get_position() const -> const glm::vec3& {
	return _position;
}

auto Transform::get_rotation() const -> glm::vec3 {
	return glm::eulerAngles(_rotation);
}

auto Transform::get_scale() const -> const glm::vec3& {
	return _scale;
}

auto Transform::get_model() const -> glm::mat4 {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), _position);
	glm::mat4 rotation = glm::mat4_cast(_rotation);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), _scale);
	return translation * rotation * scale;
}

} // namespace void_engine::utility
