module;

#include <glm/gtc/constants.hpp>

export module void_engine.graphics:camera.perspective;

import :camera;
import :camera.enums;

import glm;

export namespace void_engine::graphics::camera {

class PerspectiveCamera : public Camera {
public:
	void set_fov(float fov);
	void set_aspect(float aspect);
	void set_aspect(const glm::vec2& size);
	void set_size(const glm::vec2& size) override;
	[[nodiscard]]
	auto get_fov() const -> float;
	[[nodiscard]]
	auto get_aspect() const -> float;
	[[nodiscard]]
	auto get_type() const -> Type override;

protected:
	float _fov = glm::quarter_pi<float>();
	float _aspect = 0.0f;

	void update_projection() override;
};

} // namespace void_engine::graphics::camera
