#ifndef VOID_ENGINE_UTILITY_TRANSFORM_HPP
#define VOID_ENGINE_UTILITY_TRANSFORM_HPP

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace void_engine::utility {

class Transform {
public:
	Transform(const Transform&) = default;
	Transform(Transform&&) = default;
	auto operator=(const Transform&) -> Transform& = default;
	auto operator=(Transform&&) -> Transform& = default;
	Transform() = default;
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	~Transform() = default;

	void translate(const glm::vec3& translation);
	void rotate(const glm::vec3& rotation);
	void scale(const glm::vec3& scale);

	void set_position(const glm::vec3& position);
	void set_rotation(const glm::vec3& rotation);
	void set_scale(const glm::vec3& scale);

	[[nodiscard]] auto get_position() const -> const glm::vec3&;
	[[nodiscard]] auto get_rotation() const -> const glm::vec3&;
	[[nodiscard]] auto get_scale() const -> const glm::vec3&;
	[[nodiscard]] auto get_model() const -> glm::mat4;

private:
	glm::vec3 _position{0.0f};
	glm::vec3 _rotation{0.0f};
	glm::vec3 _scale{1.0f};
};

} // namespace void_engine::utility

#endif // VOID_ENGINE_UTILITY_TRANSFORM_HPP
