#ifndef VOID_ENGINE_GRAPHICS_CAMERA_CAMERA_HPP
#define VOID_ENGINE_GRAPHICS_CAMERA_CAMERA_HPP

#include "void_engine/graphics/camera/enums.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

namespace void_engine::graphics::camera {

class Camera {
public:
	Camera(const Camera&) = default;
	Camera(Camera&&) = default;
	auto operator=(const Camera&) -> Camera& = default;
	auto operator=(Camera&&) -> Camera& = default;
	Camera() = default;
	virtual ~Camera() = default;

	void set_near_plane(float near_plane);
	void set_far_plane(float far_plane);
	void set_position(const glm::vec3& position);
	void set_rotation(const glm::vec3& rotation);
	virtual void set_size(const glm::vec2& size) = 0;

	void move(const glm::vec3& movement);
	void rotate(glm::vec3 rotation);

	[[nodiscard]] auto is_in_frustum(const glm::vec3& point) const -> bool;
	[[nodiscard]] auto get_near_plane() const -> float;
	[[nodiscard]] auto get_far_plane() const -> float;
	[[nodiscard]] auto get_position() const -> const glm::vec3&;
	[[nodiscard]] auto get_rotation() const -> glm::vec3;
	[[nodiscard]] auto get_view() const -> const glm::mat4&;
	[[nodiscard]] auto get_projection() const -> const glm::mat4&;
	[[nodiscard]] auto get_view_projection() const -> const glm::mat4&;
	[[nodiscard]] virtual auto get_type() const -> Type = 0;

protected:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::quat _orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	float _near_plane = 0.1f;
	float _far_plane = 1000.0f;

	glm::mat4 _view = glm::mat4(1.0f);
	glm::mat4 _projection = glm::mat4(1.0f);
	glm::mat4 _view_projection = glm::mat4(1.0f);

	void update_view();
	virtual void update_projection() = 0;
	void update_view_projection();
	auto calculate_rotation(const glm::vec3& rotation) -> glm::quat;
};

} // namespace void_engine::graphics::camera

#endif // !VOID_ENGINE_GRAPHICS_CAMERA_CAMERA_HPP
