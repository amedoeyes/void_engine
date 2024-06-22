#ifndef VOID_ENGINE_RENDERER_CAMERA_CAMERA_HPP
#define VOID_ENGINE_RENDERER_CAMERA_CAMERA_HPP

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"

namespace void_engine::renderer::camera {

enum class CameraType {
	orthographic,
	perspective
};

class Camera {
public:
	virtual ~Camera() = default;
	virtual void set_near_plane(float near_plane) = 0;
	virtual void set_far_plane(float far_plane) = 0;
	virtual void set_position(glm::vec3 position) = 0;
	virtual void set_rotation(glm::vec3 rotation) = 0;
	virtual void move(glm::vec3 movement) = 0;
	virtual void rotate(glm::vec3 rotation) = 0;
	[[nodiscard]] virtual auto get_near_plane() const -> float = 0;
	[[nodiscard]] virtual auto get_far_plane() const -> float = 0;
	[[nodiscard]] virtual auto get_position() const -> glm::vec3 = 0;
	[[nodiscard]] virtual auto get_rotation() const -> glm::vec3 = 0;
	[[nodiscard]] virtual auto get_view() const -> glm::mat4 = 0;
	[[nodiscard]] virtual auto get_projection() const -> glm::mat4 = 0;
	[[nodiscard]] virtual auto get_type() const -> CameraType = 0;
};

} // namespace void_engine::renderer::camera

#endif // !VOID_ENGINE_RENDERER_CAMERA_CAMERA_HPP
