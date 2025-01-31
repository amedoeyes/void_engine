import void_engine;

using namespace void_engine;

auto main() -> int {
	auto window_manager = window::WindowManager{};
	auto& window = window_manager.create("Simple", {800, 600});

	auto renderer = graphics::renderer::Renderer{};
	renderer.set_viewport_size(window.get_size());
	renderer.set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});

	window.get_events().add_listener<window::event::WindowSizeEvent>([&](const auto& event) {
		renderer.set_viewport_size(event.size);
	});

	auto timer = utility::Timer{};
	timer.start();

	while (!window.should_close()) {
		window_manager.poll_events();

		const auto time = timer.get_elapsed();

		renderer.update();
		renderer.clear();
		renderer.draw_cube_outline(
			{{0.0f, 0.0f, -5.0f}, {time, time, time}, {1.0f, 1.0f, 1.0f}}, 1.0f, {1.0f, 1.0f, 1.0f, 1.0f}
		);

		window.swap_buffers();
	}
}
