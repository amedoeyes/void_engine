#include "void_engine/graphics/camera/orthographic_camera.hpp"

#include "void_engine/graphics/camera/enums.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float2.hpp>

namespace void_engine::graphics::camera {

void OrthographicCamera::set_left(float left) {
	_left = left;
	update_projection();
}

void OrthographicCamera::set_right(float right) {
	_right = right;
	update_projection();
}

void OrthographicCamera::set_bottom(float bottom) {
	_bottom = bottom;
	update_projection();
}

void OrthographicCamera::set_top(float top) {
	_top = top;
	update_projection();
}

void OrthographicCamera::set_dimensions(float left, float right, float bottom, float top) {
	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;
	update_projection();
}

void OrthographicCamera::set_dimensions(const glm::vec2& dimensions) {
	_left = -dimensions.x / 2.f;
	_right = dimensions.x / 2.f;
	_bottom = -dimensions.y / 2.f;
	_top = dimensions.y / 2.f;
	update_projection();
}

void OrthographicCamera::set_zoom(float zoom) {
	_zoom = zoom;
	update_projection();
}

void OrthographicCamera::zoom(float zoom) {
	_zoom *= zoom;
	update_projection();
}

auto OrthographicCamera::get_left() const -> float {
	return _left;
}

auto OrthographicCamera::get_right() const -> float {
	return _right;
}

auto OrthographicCamera::get_bottom() const -> float {
	return _bottom;
}

auto OrthographicCamera::get_top() const -> float {
	return _top;
}

auto OrthographicCamera::get_zoom() const -> float {
	return _zoom;
}

auto OrthographicCamera::get_type() const -> Type {
	return Type::orthographic;
}

void OrthographicCamera::update_projection() {
	_projection = glm::ortho(
		_left * _zoom, _right * _zoom, _bottom * _zoom, _top * _zoom, _near_plane, _far_plane
	);
	update_view_projection();
}

} // namespace void_engine::graphics::camera
