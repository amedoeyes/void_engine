#ifndef VOID_ENGINE_GRAPHICS_GEOMETRY_POLYGON_HPP
#define VOID_ENGINE_GRAPHICS_GEOMETRY_POLYGON_HPP

#include "void_engine/graphics/mesh.hpp"

#include <glm/ext/vector_float2.hpp>
#include <vector>

namespace void_engine::graphics::geometry {

auto generate_polygon_vertices(unsigned int sides) -> std::vector<glm::vec2>;
auto create_polygon_mesh(const std::vector<glm::vec2>& vertices) -> Mesh;
auto create_polygon_outline_mesh(const std::vector<glm::vec2>& vertices) -> Mesh;

} // namespace void_engine::graphics::geometry

#endif // !VOID_ENGINE_GRAPHICS_GEOMETRY_POLYGON_HPP
