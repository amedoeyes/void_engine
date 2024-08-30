#ifndef VOID_ENGINE_RENDERER_GEOMETRY_CIRCLE_HPP
#define VOID_ENGINE_RENDERER_GEOMETRY_CIRCLE_HPP

#include "void_engine/renderer/mesh.hpp"
namespace void_engine::renderer::geometry {

auto create_circle_mesh(unsigned int segments) -> Mesh;
auto create_circle_outline_mesh(unsigned int segments) -> Mesh;

} // namespace void_engine::renderer::geometry

#endif // !VOID_ENGINE_RENDERER_GEOMETRY_CIRCLE_HPP
