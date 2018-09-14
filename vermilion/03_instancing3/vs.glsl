#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

layout(location = 2) in vec4 color;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform samplerBuffer color_tbo;
uniform samplerBuffer model_matrix_tbo;

out VERTEX{
    vec3 normal;
    vec4 color;
} vertex;

void main() {
    vec4 color = texelFetch(color_tbo, gl_InstanceID);

    vec4 col1 = texelFetch(model_matrix_tbo, gl_InstanceID * 4);
    vec4 col2 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 1);
    vec4 col3 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 2);
    vec4 col4 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 3);

    mat4 model_matrix = mat4(col1, col2, col3, col4);

    mat4 model_view_matrix = view_matrix * model_matrix;

    gl_Position = projection_matrix * (model_view_matrix * position);

    vertex.normal = mat3(model_view_matrix) * normal;
    vertex.color = color;
}
