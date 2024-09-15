#ifndef VOID_ENGINE_RESOURCE_TEXTURE_HPP
#define VOID_ENGINE_RESOURCE_TEXTURE_HPP

#include "void_engine/resource/texture/enums.hpp"

#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_int3.hpp>

namespace void_engine::resource {

class Texture {
public:
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;
	auto operator=(const Texture& other) -> Texture&;
	auto operator=(Texture&& other) noexcept -> Texture&;
	explicit Texture(TextureTarget target);
	~Texture();

	void bind() const;
	void unbind() const;
	void bind_unit(unsigned int unit) const;

	void set_texture_storage_2d(
		unsigned int levels, TextureInternalFormat internal_format, const glm::ivec2& size
	);

	void set_texture_storage_3d(
		unsigned int levels, TextureInternalFormat internal_format, const glm::ivec3& size
	);

	void set_sub_image_2d(
		unsigned int level, const glm::ivec2& offset, const glm::ivec2& size, TextureFormat format,
		const void* pixels
	) const;

	void set_sub_image_3d(
		unsigned int level, const glm::ivec3& offset, const glm::ivec3& size, TextureFormat format,
		const void* pixels
	) const;

	void generate_mipmap() const;

	void set_depth_stencil_mode(TextureDepthStencilMode mode) const;

	void set_base_level(int level) const;
	void set_max_level(int level) const;

	void set_border_color(const glm::vec4& color) const;

	void set_compare_func(TextureCompareFunc func) const;
	void set_compare_mode(TextureCompareMode mode) const;

	void set_min_filter(TextureMinFilter filter) const;
	void set_mag_filter(TextureMagFilter filter) const;

	void set_min_lod(float lod) const;
	void set_max_lod(float lod) const;
	void set_lod_bias(float bias) const;

	void set_swizzle_r(TextureSwizzle swizzle) const;
	void set_swizzle_g(TextureSwizzle swizzle) const;
	void set_swizzle_b(TextureSwizzle swizzle) const;
	void set_swizzle_a(TextureSwizzle swizzle) const;

	void set_wrap_s(TextureWrap wrap) const;
	void set_wrap_t(TextureWrap wrap) const;
	void set_wrap_r(TextureWrap wrap) const;

	[[nodiscard]] auto get_size() const -> const glm::ivec3&;

private:
	unsigned int _id = 0;
	TextureTarget _target;
	glm::ivec3 _size = glm::ivec3(0);
	TextureInternalFormat _internal_format = TextureInternalFormat::none;
};

} // namespace void_engine::resource

#endif // !VOID_ENGINE_RESOURCE_TEXTURE_HPP
