#version 460 core

layout(location = 0) in vec2 i_uv;

layout(location = 0) out vec4 o_color;

layout(binding = 0) uniform sampler2D u_texture;
layout(location = 2) uniform vec4 u_color;

void main() {
    vec4 font_color = vec4(1.0f, 1.0f, 1.0f, texture(u_texture, i_uv).r);
    o_color = font_color * u_color;
}
