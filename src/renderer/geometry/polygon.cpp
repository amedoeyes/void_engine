#include "void_engine/renderer/geometry/polygon.hpp"

#include "void_engine/renderer/geometry/attributes.hpp"
#include "void_engine/renderer/mesh.hpp"
#include "void_engine/renderer/renderer/enums.hpp"

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <vector>

namespace void_engine::renderer::geometry {

namespace {

auto generate_polygon_attributes(const std::vector<glm::vec2>& vertices) -> Attributes {
	std::vector<glm::vec3> positions{{0.0f, 0.0f, 0.0f}};
	std::vector<glm::vec3> normals{{0.0f, 0.0f, 1.0f}};
	std::vector<glm::vec2> uvs{{0.5f, 0.5f}};
	const std::vector<unsigned int> indices;
	for (auto vertex : vertices) {
		positions.emplace_back(vertex.x, vertex.y, 0.0f);
		normals.emplace_back(0.0f, 0.0f, 1.0f);
		uvs.emplace_back((vertex.x + 1.0f) * 0.5f, (vertex.y + 1.0f) * 0.5f);
	}
	return {positions, normals, uvs};
}

} // namespace

auto generate_polygon_vertices(unsigned int sides) -> std::vector<glm::vec2> {
	std::vector<glm::vec2> vertices;
	vertices.reserve(sides);
	const float step = glm::two_pi<float>() / static_cast<float>(sides);
	const float offset = glm::half_pi<float>() - (sides % 2 == 0 ? step * 0.5f : 0.0f);
	for (unsigned int i = 0; i < sides; ++i) {
		const float angle = offset + (static_cast<float>(i) * step);
		vertices.emplace_back(glm::cos(angle), glm::sin(angle));
	}
	return vertices;
}

auto create_polygon_mesh(const std::vector<glm::vec2>& vertices) -> Mesh {
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < vertices.size(); ++i) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(((i + 1) % vertices.size()) + 1);
	}
	const Attributes attributes = generate_polygon_attributes(vertices);
	Mesh mesh;
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

auto create_polygon_outline_mesh(const std::vector<glm::vec2>& vertices) -> Mesh {
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < vertices.size(); ++i) {
		indices.push_back(i + 1);
		indices.push_back(((i + 1) % vertices.size()) + 1);
	}
	const Attributes attributes = generate_polygon_attributes(vertices);
	Mesh mesh(PrimitiveType::lines);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

} // namespace void_engine::renderer::geometry
