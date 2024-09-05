#include "void_engine/graphics/geometry/quad.hpp"

#include "void_engine/graphics/geometry/attributes.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"

#include <vector>

namespace void_engine::graphics::geometry {

static const Attributes attributes = {
	.positions =
		{
			{1.0f, 1.0f, 0.0f},
			{1.0f, -1.0f, 0.0f},
			{-1.0f, -1.0f, 0.0f},
			{-1.0f, 1.0f, 0.0f},
		},
	.normals =
		{
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
		},
	.uvs =
		{
			{1.0f, 1.0f},
			{1.0f, 0.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f},
		},
};

auto create_quad_mesh() -> Mesh {
	const std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
	Mesh mesh;
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

auto create_quad_outline_mesh() -> Mesh {
	const std::vector<unsigned int> indices = {0, 1, 1, 2, 2, 3, 3, 0};
	Mesh mesh(PrimitiveType::lines);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

} // namespace void_engine::graphics::geometry
