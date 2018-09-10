#version 330

uniform mat4 model_view_projection_matrix;

layout (location = 0) in vec4 position;

void main() {
    gl_Position = model_view_projection_matrix * position;
}
