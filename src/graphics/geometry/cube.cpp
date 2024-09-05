#include "void_engine/graphics/geometry/cube.hpp"

#include "void_engine/graphics/geometry/attributes.hpp"
#include "void_engine/graphics/mesh.hpp"
#include "void_engine/graphics/renderer/enums.hpp"

#include <vector>

namespace void_engine::graphics::geometry {

static const Attributes attributes = {
	.positions =
		{
			{-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
			{-1.0f, -1.0f, 1.0f},	 {1.0f, -1.0f, 1.0f},	 {1.0f, 1.0f, 1.0f},	{-1.0f, 1.0f, 1.0f},
			{-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f},
			{1.0f, -1.0f, -1.0f},	 {1.0f, 1.0f, -1.0f},	 {1.0f, 1.0f, 1.0f},	{1.0f, -1.0f, 1.0f},
			{-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f},
			{-1.0f, 1.0f, -1.0f},	 {1.0f, 1.0f, -1.0f},	 {1.0f, 1.0f, 1.0f},	{-1.0f, 1.0f, 1.0f},
		},
	.normals =
		{
			{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
			{0.0f, 0.0f, 1.0f},	 {0.0f, 0.0f, 1.0f},	{0.0f, 0.0f, 1.0f},	 {0.0f, 0.0f, 1.0f},
			{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},	 {1.0f, 0.0f, 0.0f},	{1.0f, 0.0f, 0.0f},	 {1.0f, 0.0f, 0.0f},
			{0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},	 {0.0f, 1.0f, 0.0f},	{0.0f, 1.0f, 0.0f},	 {0.0f, 1.0f, 0.0f},
		},
	.uvs =
		{
			{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
			{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
			{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
			{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
		},
};

auto create_cube_mesh() -> Mesh {
	static const std::vector<unsigned int> indices = {
		0,	1,	2,	0,	2,	3,	4,	5,	6,	4,	6,	7,	8,	9,	10, 8,	10, 11,
		12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23,
	};
	Mesh mesh;
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

auto create_cube_outline_mesh() -> Mesh {
	static const std::vector<unsigned int> indices = {
		0,	1,	1,	2,	2,	3,	3,	0,	4,	5,	5,	6,	6,	7,	7,	4,	8,	9,	9,	10, 10, 11, 11, 8,
		12, 13, 13, 14, 14, 15, 15, 12, 16, 17, 17, 18, 18, 19, 19, 16, 20, 21, 21, 22, 22, 23, 23, 20,
	};
	Mesh mesh(PrimitiveType::lines);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.positions);
	mesh.add_attribute<float>(3), mesh.add_vertex_buffer(attributes.normals);
	mesh.add_attribute<float>(2), mesh.add_vertex_buffer(attributes.uvs);
	mesh.set_indices(indices);
	return mesh;
}

} // namespace void_engine::graphics::geometry
