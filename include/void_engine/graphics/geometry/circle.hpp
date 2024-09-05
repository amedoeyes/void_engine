#ifndef VOID_ENGINE_GRAPHICS_GEOMETRY_CIRCLE_HPP
#define VOID_ENGINE_GRAPHICS_GEOMETRY_CIRCLE_HPP

#include "void_engine/graphics/mesh.hpp"
namespace void_engine::graphics::geometry {

auto create_circle_mesh(unsigned int segments) -> Mesh;
auto create_circle_outline_mesh(unsigned int segments) -> Mesh;

} // namespace void_engine::graphics::geometry

#endif // !VOID_ENGINE_GRAPHICS_GEOMETRY_CIRCLE_HPP
