#ifndef VOID_ENGINE_RENDERER_GEOMETRY_CUBE_HPP
#define VOID_ENGINE_RENDERER_GEOMETRY_CUBE_HPP

#include "void_engine/renderer/mesh.hpp"
namespace void_engine::renderer::geometry {

auto create_cube_mesh() -> Mesh;
auto create_cube_outline_mesh() -> Mesh;

} // namespace void_engine::renderer::geometry

#endif // !VOID_ENGINE_RENDERER_GEOMETRY_CUBE_HPP
