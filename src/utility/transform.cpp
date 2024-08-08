#include "void_engine/utility/transform.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

namespace void_engine::utility {

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
	_position(position),
	_rotation(rotation),
	_scale(scale) {
}

void Transform::translate(const glm::vec3& translation) {
	_position += translation;
}

void Transform::rotate(const glm::vec3& rotation) {
	_rotation += rotation;
}

void Transform::scale(const glm::vec3& scale) {
	_scale *= scale;
}

void Transform::set_position(const glm::vec3& position) {
	_position = position;
}

void Transform::set_rotation(const glm::vec3& rotation) {
	_rotation = rotation;
}

void Transform::set_scale(const glm::vec3& scale) {
	_scale = scale;
}

auto Transform::get_position() const -> const glm::vec3& {
	return _position;
}

auto Transform::get_rotation() const -> const glm::vec3& {
	return _rotation;
}

auto Transform::get_scale() const -> const glm::vec3& {
	return _scale;
}

auto Transform::get_model() const -> glm::mat4 {
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, _position);
	model = glm::rotate(model, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, _scale);
	return model;
}

} // namespace void_engine::utility
