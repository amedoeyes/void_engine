export module void_engine.utility.transform;

import glm;

export namespace void_engine::utility {

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
	void rotate(float angle, const glm::vec3& axis);
	void rotate(const glm::vec3& rotation);
	void scale(const glm::vec3& scale);

	void set_position(const glm::vec3& position);
	void set_rotation(float angle, const glm::vec3& axis);
	void set_rotation(const glm::vec3& rotation);
	void set_scale(const glm::vec3& scale);

	[[nodiscard]] auto get_position() const -> const glm::vec3&;
	[[nodiscard]] auto get_rotation() const -> glm::vec3;
	[[nodiscard]] auto get_scale() const -> const glm::vec3&;
	[[nodiscard]] auto get_model() const -> const glm::mat4&;

private:
	glm::vec3 _position{0.0f};
	glm::quat _rotation{1.0f, 0.0f, 0.0f, 0.0f};
	glm::vec3 _scale{1.0f};
	mutable glm::mat4 _model{1.0f};
	mutable bool _dirty{true};
};

} // namespace void_engine::utility
