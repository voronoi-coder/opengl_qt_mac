//#version 410

attribute vec3 a_pos;

uniform mat4 u_matrix;
uniform vec2 u_screen;

varying vec2 v_pos;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 1);
    v_pos = (gl_Position.xy / gl_Position.w + 1.0) / 2.0 * u_screen;
}
