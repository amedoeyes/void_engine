import void_engine;

namespace display = void_engine::display;
namespace window = void_engine::display::window;
namespace renderer = void_engine::graphics::renderer;

auto main() -> int {
	display::DisplayManager display;
	window::Window& window = display.windows().create("main", "Simple Example", {800, 600});

	renderer::Renderer renderer;
	renderer.set_viewport_size(window.get_size());
	renderer.set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});

	window.get_event_handler().add_listener<window::event::WindowSizeEvent>(
		[&](const window::event::WindowSizeEvent& event) {
			renderer.set_viewport_size(event.size);
		}
	);

	auto timer = void_engine::utility::Timer();
	timer.start();

	while (!window.should_close()) {
		display.windows().update();

		const float time = timer.get_elapsed();

		renderer.update();
		renderer.clear();
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
