#ifndef VOID_ENGINE_RENDERER_GEOMETRY_ATTRIBUTES_HPP
#define VOID_ENGINE_RENDERER_GEOMETRY_ATTRIBUTES_HPP

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>

namespace void_engine::renderer::geometry {

struct Attributes {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
};

} // namespace void_engine::renderer::geometry

#endif // !VOID_ENGINE_RENDERER_GEOMETRY_ATTRIBUTES_HPP
