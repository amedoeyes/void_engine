#include "void_engine/graphics/camera/perspective_camera.hpp"

#include "void_engine/graphics/camera/enums.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float2.hpp>

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

auto PerspectiveCamera::get_fov() const -> float {
	return _fov;
}

auto PerspectiveCamera::get_aspect() const -> float {
	return _aspect;
}

auto PerspectiveCamera::get_type() const -> Type {
	return Type::perspective;
}

void PerspectiveCamera::update_projection() {
	_projection = glm::perspective(_fov, _aspect, _near_plane, _far_plane);
	update_view_projection();
}

} // namespace void_engine::graphics::camera
