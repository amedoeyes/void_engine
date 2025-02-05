export module void_engine.window:video_mode;

import glm;
import std;

export namespace void_engine::window {

struct video_mode {
	glm::ivec2 size;
	glm::ivec3 color_bits;
	std::int32_t refresh_rate;
};

} // namespace void_engine::window
