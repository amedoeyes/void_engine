#ifndef VOID_ENGINE_GRAPHICS_GEOMETRY_CUBE_HPP
#define VOID_ENGINE_GRAPHICS_GEOMETRY_CUBE_HPP

#include "void_engine/graphics/mesh.hpp"
namespace void_engine::graphics::geometry {

auto create_cube_mesh() -> Mesh;
auto create_cube_outline_mesh() -> Mesh;

} // namespace void_engine::graphics::geometry

#endif // !VOID_ENGINE_GRAPHICS_GEOMETRY_CUBE_HPP
