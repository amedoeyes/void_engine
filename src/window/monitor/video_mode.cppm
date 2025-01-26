export module void_engine.window:video_mode;

import glm;

export namespace void_engine::window {

struct VideoMode {
	glm::ivec2 size;
	glm::ivec3 color_bits;
	int refresh_rate;
};

} // namespace void_engine::window
