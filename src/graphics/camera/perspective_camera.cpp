module;

#include <glm/ext/matrix_clip_space.hpp>

module void_engine.graphics;

import :camera.perspective;
import :camera.enums;

import glm;

namespace void_engine::graphics::camera {

void PerspectiveCamera::set_fov(float fov) {
	_fov = fov;
	update_projection();
}

void PerspectiveCamera::set_aspect(float aspect) {
	_aspect = aspect;
	update_projection();
}

void PerspectiveCamera::set_aspect(const glm::vec2& size) {
	_aspect = size.x / size.y;
	update_projection();
}

void PerspectiveCamera::set_size(const glm::vec2& size) { set_aspect(size); }

auto PerspectiveCamera::get_fov() const -> float { return _fov; }

auto PerspectiveCamera::get_aspect() const -> float { return _aspect; }

auto PerspectiveCamera::get_type() const -> Type { return Type::perspective; }

void PerspectiveCamera::update_projection() {
	_projection = glm::perspective(_fov, _aspect, _near_plane, _far_plane);
	update_view_projection();
}

} // namespace void_engine::graphics::camera
