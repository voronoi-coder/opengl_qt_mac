#version 410

uniform mat4 model_matrix[4];
uniform mat4 projection_matrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

layout(location = 3) in vec4 instance_weights;
layout(location = 4) in vec4 instance_color;

out vec3 vs_fs_normal;
out vec4 vs_fs_color;

void main() {
    int n;
    mat4 m = mat4(0.0);
    vec4 pos = position;
    vec4 weights = normalize(instance_weights);
    for(n = 0; n<4;n++){
        m += (model_matrix[n]*weights[n]);
    }

    vs_fs_normal = normalize((m*vec4(normal, 0.0)).xyz);
    vs_fs_color = instance_color;
    gl_Position = projection_matrix * (m * pos);
}
