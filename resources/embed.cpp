#include "embed.hpp"

#include <cstdint>

// NOLINTBEGIN
constexpr std::uint8_t shape_shader_vert[] = {
#include "shape.vert.spv.h"
};

const std::uint8_t shape_shader_frag[] = {
#include "shape.frag.spv.h"
};

const std::uint8_t font_shader_vert[] = {
#include "font.vert.spv.h"
};

const std::uint8_t font_screen_shader_vert[] = {
#include "font_screen.vert.spv.h"
};

const std::uint8_t font_shader_frag[] = {
#include "font.frag.spv.h"
};

const std::uint8_t liberation_font[] = {
#include "liberation.ttf.h"
};
// NOLINTEND

const auto shape_shader_vert_bytes = std::as_bytes(std::span<const std::uint8_t>(shape_shader_vert));

const auto shape_shader_frag_bytes = std::as_bytes(std::span<const std::uint8_t>(shape_shader_frag));

const auto font_shader_vert_bytes = std::as_bytes(std::span<const std::uint8_t>(font_shader_vert));

const auto font_screen_shader_vert_bytes = std::as_bytes(std::span<const std::uint8_t>(font_screen_shader_vert));

const auto font_shader_frag_bytes = std::as_bytes(std::span<const std::uint8_t>(font_shader_frag));

const auto liberation_font_bytes = std::as_bytes(std::span<const std::uint8_t>(liberation_font));
