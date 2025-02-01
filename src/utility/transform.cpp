module;

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

module void_engine.utility.transform;

import glm;

namespace void_engine::utility {

Transform::Transform(const glm::vec3& position,
                     const glm::vec3& rotation,
                     const glm::vec3& scale,
                     const glm::vec3& origin)
	: _position(position),
		_rotation(rotation),
		_scale(scale),
		_origin(origin) {}

void Transform::translate(const glm::vec3& translation) {
	_position += translation;
	_dirty = true;
}

void Transform::rotate(float angle, const glm::vec3& axis) {
	_rotation = glm::angleAxis(angle, axis) * _rotation;
	_dirty = true;
}

void Transform::rotate(const glm::vec3& rotation) {
	_rotation = glm::quat(rotation) * _rotation;
	_dirty = true;
}

void Transform::scale(const glm::vec3& scale) {
	_scale *= scale;
	_dirty = true;
}

void Transform::set_position(const glm::vec3& position) {
	_position = position;
	_dirty = true;
}

void Transform::set_rotation(float angle, const glm::vec3& axis) {
	_rotation = glm::angleAxis(angle, axis);
	_dirty = true;
}

void Transform::set_rotation(const glm::vec3& rotation) {
	_rotation = glm::quat(rotation);
	_dirty = true;
}

void Transform::set_scale(const glm::vec3& scale) {
	_scale = scale;
	_dirty = true;
}

void Transform::set_origin(const glm::vec3& origin) {
	_origin = origin;
	_dirty = true;
}

auto Transform::get_position() const -> const glm::vec3& { return _position; }

auto Transform::get_rotation() const -> glm::vec3 { return glm::eulerAngles(_rotation); }

auto Transform::get_scale() const -> const glm::vec3& { return _scale; }

auto Transform::get_origin() const -> const glm::vec3& { return _origin; }

auto Transform::get_model() const -> const glm::mat4& {
	if (_dirty) {
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, _position);
		_model = _model * glm::mat4_cast(_rotation);
		_model = glm::translate(_model, -_origin);
		_model = glm::scale(_model, _scale);
		_model = glm::translate(_model, _origin);
		_dirty = false;
	}
	return _model;
}

} // namespace void_engine::utility
