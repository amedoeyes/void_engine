export module void_engine.resources:image;

import glm;
import std;

export namespace void_engine::resources {

class image {
public:
	image(std::span<const std::byte> bytes,
	      const glm::ivec2& size,
	      std::int32_t bit_depth,
	      std::int32_t channels) noexcept;
	explicit image(std::span<const std::byte> bytes);

	[[nodiscard]]
	auto compress() const -> std::vector<std::byte>;

	auto flip() noexcept -> void;

	[[nodiscard]]
	auto data() const noexcept -> std::span<const std::byte>;

	[[nodiscard]]
	auto size() const noexcept -> const glm::ivec2&;

	[[nodiscard]]
	auto bit_depth() const noexcept -> std::int32_t;

	[[nodiscard]]
	auto channels() const noexcept -> std::int32_t;

private:
	std::vector<std::byte> data_;
	glm::ivec2 size_ = {0, 0};
	std::int32_t bit_depth_;
	std::int32_t channels_;
};

} // namespace void_engine::resources
