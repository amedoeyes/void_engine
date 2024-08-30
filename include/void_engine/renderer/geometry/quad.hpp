#ifndef VOID_ENGINE_RENDERER_GEOMETRY_QUAD_HPP
#define VOID_ENGINE_RENDERER_GEOMETRY_QUAD_HPP

#include "void_engine/renderer/mesh.hpp"

namespace void_engine::renderer::geometry {

auto create_quad_mesh() -> Mesh;
auto create_quad_outline_mesh() -> Mesh;

} // namespace void_engine::renderer::geometry

#endif // !VOID_ENGINE_RENDERER_GEOMETRY_QUAD_HPP
