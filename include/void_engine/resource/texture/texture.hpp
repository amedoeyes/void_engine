#ifndef VOID_ENGINE_RESOURCE_TEXTURE_HPP
#define VOID_ENGINE_RESOURCE_TEXTURE_HPP

#include "void_engine/resource/texture/enums.hpp"

#include <cstddef>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_int3.hpp>
#include <vector>

namespace void_engine::resource::texture {

class Texture {
public:
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;
	auto operator=(const Texture& other) -> Texture&;
	auto operator=(Texture&& other) noexcept -> Texture&;
	explicit Texture(Target target);
	~Texture();

	void bind() const;
	void unbind() const;
	void bind_unit(unsigned int unit) const;

	void set_texture_storage_2d(
		unsigned int levels, InternalFormat internal_format, const glm::ivec2& size
	);

	void set_texture_storage_3d(
		unsigned int levels, InternalFormat internal_format, const glm::ivec3& size
	);

	void set_sub_image_2d(
		unsigned int level, const glm::ivec2& offset, const glm::ivec2& size, Format format,
		const void* pixels
	) const;

	void set_sub_image_3d(
		unsigned int level, const glm::ivec3& offset, const glm::ivec3& size, Format format,
		const void* pixels
	) const;

	void generate_mipmap() const;

	void set_depth_stencil_mode(DepthStencilMode mode) const;

	void set_base_level(int level) const;
	void set_max_level(int level) const;

	void set_border_color(const glm::vec4& color) const;

	void set_compare_func(CompareFunc func) const;
	void set_compare_mode(CompareMode mode) const;

	void set_min_filter(MinFilter filter) const;
	void set_mag_filter(MagFilter filter) const;

	void set_min_lod(float lod) const;
	void set_max_lod(float lod) const;
	void set_lod_bias(float bias) const;

	void set_swizzle_r(Swizzle swizzle) const;
	void set_swizzle_g(Swizzle swizzle) const;
	void set_swizzle_b(Swizzle swizzle) const;
	void set_swizzle_a(Swizzle swizzle) const;

	void set_wrap_s(Wrap wrap) const;
	void set_wrap_t(Wrap wrap) const;
	void set_wrap_r(Wrap wrap) const;

	[[nodiscard]] auto get_data(Format format) const -> std::vector<std::byte>;
	[[nodiscard]] auto get_size() const -> const glm::ivec3&;

private:
	unsigned int _id = 0;
	Target _target;
	glm::ivec3 _size = glm::ivec3(1);
	InternalFormat _internal_format = InternalFormat::none;

	[[nodiscard]] static auto get_bytes_per_pixel(Format format) -> unsigned int;
};

} // namespace void_engine::resource::texture

#endif // !VOID_ENGINE_RESOURCE_TEXTURE_HPP
