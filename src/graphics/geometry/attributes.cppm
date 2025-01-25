export module void_engine.graphics:geometry.attributes;

import std;
import glm;

namespace void_engine::graphics::geometry {

struct Attributes {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
};

} // namespace void_engine::graphics::geometry
