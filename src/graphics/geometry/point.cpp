#include "void_engine/graphics/geometry/point.hpp"

#include "void_engine/graphics/geometry/attributes.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"

#include <vector>

namespace void_engine::graphics::geometry {

static const Attributes attributes = {
	.positions =
		{
			{0.0f, 0.0f, 0.0f},
		},
	.normals =
		{
			{0.0f, 0.0f, 1.0f},
		},
	.uvs =
		{
			{0.5f, 0.5f},
		},
};

auto create_point_mesh() -> Mesh {
	const std::vector<unsigned int> indices = {0};
	Mesh mesh(renderer::PrimitiveType::points);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

} // namespace void_engine::graphics::geometry
