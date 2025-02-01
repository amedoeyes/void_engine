#include <ctime>
#include <glm/gtc/constants.hpp>
import std;
import glm;
import void_engine;

using namespace void_engine;

static auto get_time() -> double {
	const auto now = std::chrono::system_clock::now();
	const auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

static auto get_local_offset() -> double {
	const auto now = std::chrono::system_clock::now();
	const auto time = std::chrono::system_clock::to_time_t(now);
	auto local_tm = std::tm{};
	auto utc_tm = std::tm{};
	(void)localtime_r(&time, &local_tm);
	(void)gmtime_r(&time, &utc_tm);
	const auto local_time = std::mktime(&local_tm);
	const auto utc_time = std::mktime(&utc_tm);
	return std::difftime(local_time, utc_time) / 3600.0;
}

auto main() -> int {
	auto window_manager = window::window_manager{};
	auto& window = window_manager.create("Clock", {800, 600});

	auto renderer = graphics::renderer::Renderer{};
	renderer.set_viewport_size(window.size());
	renderer.set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});
	renderer.get_camera().set_position({0.0f, 0.0f, 5.0f});

	window.events().add_listener<window::event::WindowSizeEvent>([&](const auto& event) {
		renderer.set_viewport_size(event.size);
	});

	const auto local_offset = get_local_offset();
	const auto angle_offset = glm::half_pi<double>();
	const auto scale = 2.0f;

	while (!window.should_close()) {
		window_manager.poll_events();

		const auto time = static_cast<long>(get_time());
		const auto seconds = time % 60;
		const auto minutes = (time / 60) % 60;
		const auto hours = (time / 3'600 + static_cast<long>(local_offset)) % 12;

		const auto seconds_angle = ((static_cast<double>(seconds) / 60.0) * glm::two_pi<double>()) + angle_offset;
		const auto minutes_angle = ((static_cast<double>(minutes) / 60.0) * glm::two_pi<double>()) + angle_offset;
		const auto hours_angle = ((static_cast<double>(hours) / 12.0) * glm::two_pi<double>()) + angle_offset;

		renderer.update();
		renderer.clear();

		renderer.draw_circle_outline(
			{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {scale, scale, 1.0f}}, 2.0f, {1.0f, 1.0f, 1.0f, 1.0f}
		);

		for (auto i : std::views::iota(0, 60)) {
			const auto angle = ((i / 60.0) * glm::two_pi<double>()) + angle_offset;
			const auto length = i % 5 == 0 ? 0.1f : 0.05f;
			const auto start = glm::vec3{-glm::cos(angle) * scale, glm::sin(angle) * scale, 0.0f};
			const auto end = glm::vec3{-glm::cos(angle) * (scale - length), glm::sin(angle) * (scale - length), 0.0f};
			const auto width = i % 5 == 0 ? 4.0f : 1.0f;
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
