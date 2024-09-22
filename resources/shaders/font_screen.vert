#version 460 core

layout(location = 0) in vec2 i_position;
layout(location = 1) in vec2 i_uv;

layout(location = 0) out vec2 o_uv;

layout(location = 0) uniform mat4 u_model;
layout(location = 1) uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_model * vec4(i_position, 1.0f, 1.0f);
    o_uv = i_uv;
}
