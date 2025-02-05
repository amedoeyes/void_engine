module;

#include <cassert>
#include <png.h>

module void_engine.resources;

import glm;
import std;

namespace void_engine::resources {

class png_context {
public:
	enum class type : std::uint8_t { read, write };

	png_struct* png = nullptr;
	png_info* info = nullptr;

	png_context(const png_context&) = delete;
	png_context(png_context&&) = delete;
	auto operator=(const png_context&) -> png_context& = delete;
	auto operator=(png_context&&) -> png_context& = delete;

	explicit png_context(type type) : type_{type} {
		switch (type_) {
			using enum type;
		case read:
			png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, error_callback, warning_callback);
			if (png == nullptr) throw std::runtime_error("Failed to create PNG read struct");
			break;
		case write:
			png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, error_callback, warning_callback);
			if (png == nullptr) throw std::runtime_error("Failed to create PNG write struct");
			break;
		}
		info = png_create_info_struct(png);
		if (info == nullptr) {
			destroy();
			throw std::runtime_error("Failed to create PNG info struct");
		}
	}

	~png_context() {
		destroy();
	}

private:
	type type_;

	auto destroy() noexcept -> void {
		switch (type_) {
			using enum type;
		case read: png_destroy_read_struct(&png, &info, nullptr); break;
		case write: png_destroy_write_struct(&png, &info); break;
		}
	}

	static void error_callback(png_struct* /*png*/, const char* error_msg) {
		throw std::runtime_error(error_msg);
	}

	static void warning_callback(png_struct* /*png*/, const char* warning_msg) {
		throw std::runtime_error(warning_msg);
	}
};

image::image(std::span<const std::byte> bytes,
             const glm::ivec2& size,
             std::int32_t bit_depth,
             std::int32_t channels) noexcept
	: data_{bytes.begin(), bytes.end()},
		size_{size},
		bit_depth_{bit_depth},
		channels_{channels} {}

image::image(const std::span<const std::byte> bytes) {
	const auto ctx = png_context{png_context::type::read};

	auto reader = std::pair{bytes, 0ul};
	png_set_read_fn(ctx.png, &reader, [](png_struct* png, unsigned char* out_bytes, std::size_t size) {
		auto& [bytes, offset] = *static_cast<std::pair<std::span<const std::byte>, std::size_t>*>(png_get_io_ptr(png));
		std::memcpy(out_bytes, bytes.data() + offset, size);
		offset += size;
	});

	png_read_info(ctx.png, ctx.info);
	png_set_expand(ctx.png);
	png_read_update_info(ctx.png, ctx.info);

	const auto row_bytes = png_get_rowbytes(ctx.png, ctx.info);
	size_ = {png_get_image_width(ctx.png, ctx.info), png_get_image_height(ctx.png, ctx.info)};
	data_.resize(row_bytes * size_.y);
	bit_depth_ = png_get_bit_depth(ctx.png, ctx.info);
	channels_ = png_get_channels(ctx.png, ctx.info);

	auto data_2d = std::views::iota(0, size_.y) //
	             | std::views::transform([&](const auto i) {
									 return std::bit_cast<unsigned char*>(std::next(data_.begin(), i * row_bytes));
								 })
	             | std::ranges::to<std::vector>();
	png_read_image(ctx.png, data_2d.data());
}

auto image::compress() const -> std::vector<std::byte> {
	const auto ctx = png_context{png_context::type::write};

	auto bytes = std::vector<std::byte>{};
	png_set_write_fn(
		ctx.png,
		&bytes,
		[](png_struct* png, unsigned char* bytes, std::size_t size) {
			auto* out_bytes = static_cast<std::vector<unsigned char>*>(png_get_io_ptr(png));
			const auto bytes_span = std::span(bytes, size);
			out_bytes->insert(out_bytes->end(), bytes_span.begin(), bytes_span.end());
		},
		nullptr);

	auto color_type = 0;
	switch (channels_) {
	case 1: color_type = PNG_COLOR_TYPE_GRAY; break;
	case 2: color_type = PNG_COLOR_TYPE_GRAY_ALPHA; break;
	case 3: color_type = PNG_COLOR_TYPE_RGB; break;
	case 4: color_type = PNG_COLOR_TYPE_RGB_ALPHA; break;
	default: std::unreachable();
	}
	png_set_IHDR(ctx.png,
	             ctx.info,
	             size_.x,
	             size_.y,
	             bit_depth_,
	             color_type,
	             PNG_INTERLACE_NONE,
	             PNG_COMPRESSION_TYPE_DEFAULT,
	             PNG_FILTER_TYPE_DEFAULT);
	png_write_info(ctx.png, ctx.info);

	const auto row_bytes = png_get_rowbytes(ctx.png, ctx.info);
	auto data_2d = std::views::iota(0, size_.y) //
	             | std::views::transform([&](const auto i) {
									 return std::bit_cast<unsigned char*>(std::next(data_.begin(), i * row_bytes));
								 })
	             | std::ranges::to<std::vector>();
	png_write_image(ctx.png, data_2d.data());
	png_write_end(ctx.png, nullptr);

	return bytes;
}

auto image::flip() noexcept -> void {
	const auto row_bytes = size_.x * (bit_depth_ / 8) * channels_;
	for (const auto i : std::views::iota(0l, size_.y / 2)) {
		std::ranges::swap_ranges(std::span(data_.begin() + i * row_bytes, row_bytes),
		                         std::span(data_.begin() + (size_.y - 1 - i) * row_bytes, row_bytes));
	}
}

auto image::data() const noexcept -> std::span<const std::byte> {
	return data_;
}

auto image::size() const noexcept -> const glm::ivec2& {
	return size_;
}

auto image::bit_depth() const noexcept -> std::int32_t {
	return bit_depth_;
}

auto image::channels() const noexcept -> std::int32_t {
	return channels_;
}

} // namespace void_engine::resources
