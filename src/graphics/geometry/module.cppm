export module void_engine.graphics:geometry;

import :mesh;

import std;
import glm;

export namespace void_engine::graphics::geometry {

auto create_circle_mesh(unsigned int segments) -> Mesh;
auto create_circle_outline_mesh(unsigned int segments) -> Mesh;

auto create_cube_mesh() -> Mesh;
auto create_cube_outline_mesh() -> Mesh;

auto create_line_mesh() -> Mesh;

auto create_point_mesh() -> Mesh;

// TODO: move to math module maybe
auto generate_polygon_vertices(unsigned int sides) -> std::vector<glm::vec2>;
auto create_polygon_mesh(const std::vector<glm::vec2>& vertices) -> Mesh;
auto create_polygon_outline_mesh(const std::vector<glm::vec2>& vertices) -> Mesh;

auto create_quad_mesh() -> Mesh;
auto create_quad_outline_mesh() -> Mesh;

} // namespace void_engine::graphics::geometry
