#include "void_engine/renderer/geometry/line.hpp"

#include "void_engine/renderer/geometry/attributes.hpp"
#include "void_engine/renderer/mesh.hpp"
#include "void_engine/renderer/renderer/enums.hpp"

#include <vector>

namespace void_engine::renderer::geometry {

static const Attributes attributes = {
	.positions =
		{
			{-1.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},
		},
	.normals =
		{
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
		},
	.uvs =
		{
			{0.0f, 0.0f},
			{1.0f, 0.0f},
		},
};

auto create_line_mesh() -> Mesh {
	const std::vector<unsigned int> indices = {0, 1};
	Mesh mesh(PrimitiveType::lines);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

} // namespace void_engine::renderer::geometry
