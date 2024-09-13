#version 460 core

layout(location = 0) out vec4 o_color;

layout(location = 1) uniform vec4 u_color;

void main() {
    o_color = u_color;
}
