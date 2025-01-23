#include <void_engine/graphics/renderer/renderer.hpp>

import std;
import glm;
import void_engine;

namespace display = void_engine::display;
namespace renderer = void_engine::graphics::renderer;
namespace window = void_engine::display::window;

static auto get_time() -> double {
	const auto now = std::chrono::system_clock::now();
	const auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

static auto get_local_offset() -> double {
	const auto time = static_cast<std::time_t>(get_time());
	std::tm local_tm = *std::localtime(&time);
	std::tm utc_tm = *std::gmtime(&time);
	const auto local_time = std::mktime(&local_tm);
	const auto utc_time = std::mktime(&utc_tm);
	const double offset_seconds = std::difftime(local_time, utc_time);
	return offset_seconds / 3600.0;
}

auto main() -> int {
	auto display = display::DisplayManager();
	auto& window = display.windows().create("main", "Clock", {800, 600});

	auto renderer = renderer::Renderer();
	renderer.set_viewport_size(window.get_size());
	renderer.set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});
	auto& camera = renderer.get_camera();
	camera.set_position({0.0f, 0.0f, 5.0f});

	window.get_event_handler().add_listener<window::event::WindowSizeEvent>([&](const auto& event) {
		renderer.set_viewport_size(event.size);
	});

	const double local_offset = get_local_offset();
	const auto angle_offset = glm::half_pi<double>();
	const float scale = 2.0f;

	while (!window.should_close()) {
		display.windows().update();

		const long time = static_cast<long>(get_time());
		const long seconds = time % 60;
		const long minutes = (time / 60) % 60;
		const long hours = (time / 3600 + static_cast<long>(local_offset)) % 12;

		const double seconds_angle =
			(static_cast<double>(seconds) / 60.0) * glm::two_pi<double>() + angle_offset;
		const double minutes_angle =
			(static_cast<double>(minutes) / 60.0) * glm::two_pi<double>() + angle_offset;
		const double hours_angle =
			(static_cast<double>(hours) / 12.0) * glm::two_pi<double>() + angle_offset;

		renderer.update();
		renderer.clear();

		renderer.draw_circle_outline(
			{
				{0.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f},
				{scale, scale, 1.0f},
			},
			2.0f,
			{1.0f, 1.0f, 1.0f, 1.0f}
		);

		for (int i = 0; i < 60; i++) {
			const double angle = (static_cast<double>(i) / 60.0) * glm::two_pi<double>() + angle_offset;
			const float length = i % 5 == 0 ? 0.1f : 0.05f;
			const glm::vec3 start = {-glm::cos(angle) * scale, glm::sin(angle) * scale, 0.0f};
			const glm::vec3 end = {
				-glm::cos(angle) * (scale - length), glm::sin(angle) * (scale - length), 0.0f
			};
			const float width = i % 5 == 0 ? 4.0f : 1.0f;
			renderer.draw_line(start, end, width, {1.0f, 1.0f, 1.0f, 1.0f});
		}

		renderer.draw_line(
			{0.0f, 0.0f, 0.0f},
			{-glm::cos(hours_angle) * 0.6f * scale, glm::sin(hours_angle) * 0.6f * scale, 0.0f},
			8.0f,
			{1.0f, 1.0f, 1.0f, 1.0f}
		);

		renderer.draw_line(
			{0.0f, 0.0f, 0.0f},
			{-glm::cos(minutes_angle) * 0.9f * scale, glm::sin(minutes_angle) * 0.9f * scale, 0.0f},
			4.0f,
			{1.0f, 1.0f, 1.0f, 1.0f}
		);

		renderer.draw_line(
			{0.0f, 0.0f, 0.0f},
			{-glm::cos(seconds_angle) * 0.9f * scale, glm::sin(seconds_angle) * 0.9f * scale, 0.0f},
			1.0f,
			{1.0f, 1.0f, 1.0f, 1.0f}
		);

		renderer.draw_point({0.0f, 0.0f, 0.0f}, 10.0f, {1.0f, 1.0f, 1.0f, 1.0f});

		window.swap_buffers();
	}

	return 0;
}
