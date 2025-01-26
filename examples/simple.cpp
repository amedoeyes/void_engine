import void_engine;

namespace window = void_engine::window;
namespace renderer = void_engine::graphics::renderer;

auto main() -> int {
	window::WindowManager window_manager;
	window::Window& window = window_manager.create("Simple Example", {800, 600});

	renderer::Renderer renderer;
	renderer.set_viewport_size(window.get_size());
	renderer.set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});

	window.get_events().add_listener<window::event::WindowSizeEvent>(
		[&](const window::event::WindowSizeEvent& event) {
			renderer.set_viewport_size(event.size);
		}
	);

	auto timer = void_engine::utility::Timer();
	timer.start();

	while (!window.should_close()) {
		window_manager.poll_events();

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
