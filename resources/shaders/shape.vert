#version 460 core

layout(location = 0) in vec3 i_position;

layout(location = 0) uniform mat4 u_model;

layout(binding = 0) uniform Camera {
    mat4 projection;
    mat4 view;
    mat4 view_projection;
} u_camera;

void main() {
    gl_Position = u_camera.view_projection * u_model * vec4(i_position, 1.0f);
}