#ifndef VOID_ENGINE_GRAPHICS_CAMERA_PERSPECTIVE_CAMERA_HPP
#define VOID_ENGINE_GRAPHICS_CAMERA_PERSPECTIVE_CAMERA_HPP

#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/graphics/camera/enums.hpp"

#include <glm/ext/vector_float2.hpp>
#include <glm/gtc/constants.hpp>

namespace void_engine::graphics::camera {

class PerspectiveCamera : public Camera {
public:
	void set_fov(float fov);
	void set_aspect(float aspect);
	void set_aspect(const glm::vec2& size);
	void set_size(const glm::vec2& size) override;
	[[nodiscard]] auto get_fov() const -> float;
	[[nodiscard]] auto get_aspect() const -> float;
	[[nodiscard]] auto get_type() const -> Type override;

protected:
	float _fov = glm::quarter_pi<float>();
	float _aspect = 0.0f;

	void update_projection() override;
};

} // namespace void_engine::graphics::camera

#endif // !VOID_ENGINE_GRAPHICS_CAMERA_PERSPECTIVE_CAMERA_HPP
