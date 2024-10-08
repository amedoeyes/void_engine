#include "void_engine/graphics/geometry/circle.hpp"

#include "void_engine/graphics/geometry/attributes.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"

#include <cmath>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

namespace void_engine::graphics::geometry {

namespace {

auto generate_circle_attributes(unsigned int segments) -> Attributes {
	const float step = glm::two_pi<float>() / static_cast<float>(segments);
	std::vector<glm::vec3> positions = {{0.0f, 0.0f, 0.0f}};
	std::vector<glm::vec3> normals = {{0.0f, 0.0f, 1.0f}};
	std::vector<glm::vec2> uvs = {{0.5f, 0.5f}};
	for (unsigned int i = 0; i < segments; ++i) {
		const float angle = static_cast<float>(i) * step;
		const float x = std::cos(angle);
		const float y = std::sin(angle);
		positions.emplace_back(x, y, 0.0f);
		normals.emplace_back(0.0f, 0.0f, 1.0f);
		uvs.emplace_back((x + 1.0f) * 0.5f, (y + 1.0f) * 0.5f);
	}
	return {positions, normals, uvs};
}

} // namespace

auto create_circle_mesh(unsigned int segments) -> Mesh {
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < segments; ++i) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(((i + 1) % segments) + 1);
	}
	const Attributes attributes = generate_circle_attributes(segments);
	Mesh mesh;
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

auto create_circle_outline_mesh(unsigned int segments) -> Mesh {
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < segments; ++i) {
		indices.push_back(i + 1);
		indices.push_back(((i + 1) % segments) + 1);
	}
	const Attributes attributes = generate_circle_attributes(segments);
	Mesh mesh(renderer::PrimitiveType::lines);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

} // namespace void_engine::graphics::geometry
