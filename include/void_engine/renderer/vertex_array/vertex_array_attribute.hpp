#ifndef VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_ATTRIBUTE_HPP
#define VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_ATTRIBUTE_HPP

namespace void_engine::renderer::vertex_array {

struct VertexArrayAttribute {
	unsigned int count = 0;
	unsigned int stride = 0;
	unsigned int type = 0;
	bool normalized = false;
};

} // namespace void_engine::renderer::vertex_array

#endif // !VOID_ENGINE_RENDERER_VERTEX_ARRAY_VERTEX_ARRAY_ATTRIBUTE_HPP
