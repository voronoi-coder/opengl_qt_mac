#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

layout(location = 2) in vec4 color;

layout(location = 3) in mat4 model_matrix;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out VERTEX{
    vec3 normal;
    vec4 color;
} vertex;

void main() {
    mat4 model_view_matrix = view_matrix * model_matrix;

    gl_Position = projection_matrix * (model_view_matrix * position);

    vertex.normal = mat3(model_view_matrix) * normal;

    vertex.color = color;
}
