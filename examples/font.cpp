import std;
import glm;
import void_engine;

using namespace void_engine;

auto main() -> int {
	auto window_manager = window::WindowManager();
	auto& window = window_manager.create("Font", {800, 600});

	auto renderer = graphics::renderer::Renderer();
	renderer.set_viewport_size(window.get_size());
	renderer.set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});

	window.get_events().add_listener<window::event::WindowSizeEvent>([&](const auto& event) {
		renderer.set_viewport_size(event.size);
	});

	const auto font = resources::Font("./resources/fonts/liberation.ttf");
	auto font_atlas = graphics::FontAtlas(font);
	const auto text = graphics::Text(font_atlas, "Hello, World!");

	const auto center = (text.get_size() / 2.0f) * 0.01f;

	auto timer = utility::Timer();
	timer.start();

	while (!window.should_close()) {
		window_manager.poll_events();

		const auto time = timer.get_elapsed();

		renderer.update();
		renderer.clear();

		renderer.draw_text(
			text,
			{
				{0.0f, 0.0f, -10.0f},
				{time, time, time},
				{0.01f, 0.01f, 0.01f},
				{center.x, center.y, 0.0f},
			},
			{1.0f, 1.0f, 1.0f, 1.0f}
		);

		renderer.draw_text_screen(
			std::format("Time: {:.2f}s", time), {{10, 10, 0}, {}, {0.5, 0.5, 1}}, {1.0f, 1.0f, 1.0f, 1.0f}
		);

		renderer.draw_cube_outline(
			{
				{0.0f, 0.0f, -5.0f},
				{time, time, time},
				{1.0f, 1.0f, 1.0f},
			},
			1.0f,
			{1.0f, 1.0f, 1.0f, 1.0f}
		);

		window.swap_buffers();
	}

	return 0;
}
