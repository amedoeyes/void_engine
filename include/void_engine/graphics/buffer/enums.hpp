#ifndef VOID_ENGINE_GRAPHICS_BUFFER_ENUMS_HPP
#define VOID_ENGINE_GRAPHICS_BUFFER_ENUMS_HPP

#include <cstdint>
namespace void_engine::graphics::buffer {

enum class Target : uint16_t {
	none = 0,
	array = 0x8892,
	atomic_counter = 0x92C0,
	copy_read = 0x8F36,
	copy_write = 0x8F37,
	dispatch_indirect = 0x90EE,
	draw_indirect = 0x8F3F,
	element_array = 0x8893,
	pixel_pack = 0x88EB,
	pixel_unpack = 0x88EC,
	query = 0x9192,
	shader_storage = 0x90D2,
	texture = 0x8C2A,
	transform_feedback = 0x8C8E,
	uniform = 0x8A11
};

enum class Usage : uint16_t {
	none = 0,
	stream_draw = 0x88E0,
	stream_read = 0x88E1,
	stream_copy = 0x88E2,
	static_draw = 0x88E4,
	static_read = 0x88E5,
	static_copy = 0x88E6,
	dynamic_draw = 0x88E8,
	dynamic_read = 0x88E9,
	dynamic_copy = 0x88EA
};

} // namespace void_engine::graphics::buffer

#endif // !VOID_ENGINE_GRAPHICS_BUFFER_ENUMS_HPP
