module;

#include "void_engine/graphics/buffer/uniform_buffer.hpp"
#include "void_engine/graphics/camera/camera.hpp"
#include "void_engine/resource/font/text.hpp"
#include "void_engine/resource/resource_manager.hpp"
#include "void_engine/utility/bit_mask.hpp"
#include "void_engine/utility/transform.hpp"

export module void_engine.graphics:renderer.renderer;

import :renderer.enums;
import :geometry;
import :mesh;

import std;
import glm;

export namespace void_engine::graphics::renderer {

struct DrawObjects {
	Mesh point = geometry::create_point_mesh();
	Mesh line = geometry::create_line_mesh();
	Mesh quad = geometry::create_quad_mesh();
	Mesh quad_outline = geometry::create_quad_outline_mesh();
	Mesh circle = geometry::create_circle_mesh(100);
	Mesh circle_outline = geometry::create_circle_outline_mesh(100);
	Mesh cube = geometry::create_cube_mesh();
	Mesh cube_outline = geometry::create_cube_outline_mesh();
	resource::font::Text text;
};

struct CameraUniform {
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 view_projection;
};

struct BlendFactors {
	BlendFactor source = BlendFactor::one;
	BlendFactor destination = BlendFactor::zero;
};

struct Blend {
	bool enabled = false;
	BlendEquation equation = BlendEquation::add;
	BlendFactors factors;
};

struct Clear {
	utility::BitMask<ClearFlags> flags = utility::BitMask<ClearFlags>{ClearFlags::color};
	glm::vec4 color = {0.0f, 0.0f, 0.0f, 0.0f};
};

struct CullFace {
	bool enabled = false;
	CullFaceFacet facet = CullFaceFacet::back;
	CullFaceOrientation orientation = CullFaceOrientation::ccw;
};

struct Depth {
	bool enabled = false;
	DepthFunction function = DepthFunction::less;
};

struct StencilSettings {
	StencilFunction function = StencilFunction::always;
	int reference = 0;
	unsigned int mask = 0xFF;
};

struct StencilActions {
	StencilAction stencil_fail = StencilAction::keep;
	StencilAction depth_fail = StencilAction::keep;
	StencilAction depth_pass = StencilAction::keep;
};

struct Stencil {
	bool enabled = false;
	StencilSettings settings;
	StencilActions actions;
};

struct Viewport {
	glm::ivec2 position = {0, 0};
	glm::ivec2 size = {0, 0};
};

class Renderer {
public:
	Renderer(const Renderer&) = default;
	Renderer(Renderer&&) = delete;
	auto operator=(const Renderer&) -> Renderer& = default;
	auto operator=(Renderer&&) -> Renderer& = delete;
	Renderer();
	~Renderer();

	void clear() const;
	void update();

	void draw_point(const glm::vec3& position, float size, const glm::vec4& color);
	void draw_line(const glm::vec3& start, const glm::vec3& end, float width, const glm::vec4& color);

	void draw_quad(const utility::Transform& transform, const glm::vec4& color);
	void draw_quad_outline(const utility::Transform& transform, float width, const glm::vec4& color);
	void draw_circle(const utility::Transform& transform, const glm::vec4& color);
	void draw_circle_outline(
		const utility::Transform& transform, float width, const glm::vec4& color
	);
	void draw_cube(const utility::Transform& transform, const glm::vec4& color);
	void draw_cube_outline(const utility::Transform& transform, float width, const glm::vec4& color);
	void draw_text(
		const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
	);
	void draw_text(
		std::string_view text, const utility::Transform& transform, const glm::vec4& color
	);
	void draw_text_screen(
		const resource::font::Text& text, const utility::Transform& transform, const glm::vec4& color
	);
	void draw_text_screen(
		std::string_view text, const utility::Transform& transform, const glm::vec4& color
	);

	static void draw_mesh(const Mesh& mesh);
	static void draw_mesh_instanced(const Mesh& mesh, unsigned int instances);
	static void draw_elements(PrimitiveType type, unsigned int count, void* indices);
	static void draw_elements_instanced(
		PrimitiveType type, unsigned int count, void* indices, unsigned int instances
	);

	void set_camera(camera::Camera& camera);
	void set_clear_color(const glm::vec4& color);
	void set_polygon_mode(PolygonMode mode);

	void set_blend(const Blend& blend);
	void set_blend_enabled(bool enabled);
	void set_blend_equation(BlendEquation equation);
	void set_blend_factors(const BlendFactors& factors);

	void set_cull_face(const CullFace& cull_face);
	void set_cull_face_enabled(bool enabled);
	void set_cull_face_facet(CullFaceFacet facet);
	void set_cull_face_orientation(CullFaceOrientation orientation);

	void set_depth(const Depth& depth);
	void set_depth_enabled(bool enabled);
	void set_depth_function(DepthFunction function);

	void set_stencil(const Stencil& stencil);
	void set_stencil_enabled(bool enabled);
	void set_stencil_settings(const StencilSettings& settings);
	void set_stencil_actions(const StencilActions& actions);

	void set_viewport(const Viewport& viewport);
	void set_viewport_position(const glm::ivec2& position);
	void set_viewport_size(const glm::ivec2& size);

	static void set_line_width(float width);
	static void set_point_size(float size);

	[[nodiscard]] auto get_camera() const -> camera::Camera&;
	[[nodiscard]] auto get_clear_color() const -> const glm::vec4&;
	[[nodiscard]] auto get_polygon_mode() const -> PolygonMode;
	[[nodiscard]] auto get_blend() const -> const Blend&;
	[[nodiscard]] auto get_cull_face() const -> const CullFace&;
	[[nodiscard]] auto get_depth() const -> const Depth&;
	[[nodiscard]] auto get_stencil() const -> const Stencil&;
	[[nodiscard]] auto get_viewport() const -> const Viewport&;

private:
	bool _initialized = initialize();
	resource::ResourceManager _resource_manager;
	DrawObjects _draw_objects;
	buffer::UniformBuffer<CameraUniform> _camera_uniform;
	camera::Camera* _default_camera;
	camera::Camera* _camera;
	glm::mat4 _screen_projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);
	PolygonMode _polygon_mode = PolygonMode::fill;
	Blend _blend;
	Clear _clear;
	CullFace _cull_face;
	Depth _depth;
	Stencil _stencil;
	Viewport _viewport;

	static auto initialize() -> bool;
	static void set_enabled(unsigned int capability, bool enabled);
	void update_camera_uniform();
};

} // namespace void_engine::graphics::renderer
