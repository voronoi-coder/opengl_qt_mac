uniform mat4 model_matrix;
uniform mat4 projection_matrix;

attribute vec4 position;
attribute vec4 color;

varying vec4 vs_fs_color;

void main(void) {
    const vec4 pos[3] = vec4[3](vec4(-0.3, -0.3, 0.0, 1.0), vec4(0.3, -0.3, 0.0, 1.0), vec4(-0.3, 0.3, 0.0, 1.0));
    vs_fs_color = color;
    gl_Position = projection_matrix * (model_matrix * position);
}
