#version 330
#define DEVICE_PIXEL_RATIO 2.0
// the distance over which the line edge fades out.
// Retina devices need a smaller distance to avoid aliasing.
#define ANTIALIASING 1.0 / DEVICE_PIXEL_RATIO / 2.0

#define scale 0.015873016

layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec4 a_data;

uniform mat4 u_matrix;
uniform highp vec4 u_color;
uniform mediump float u_width;

out vec4 v_color;
out vec2 v_normal;

void main() {
    vec2 a_extrude = a_data.xy - 128.0;
    float a_direction = mod(a_data.z, 4.0) - 1.0;

    mediump vec2 normal = mod(a_pos, 2.0);
    normal.y = sign(normal.y - 0.5);
    v_normal = normal;

    float halfwidth = u_width /2.0;

    mediump vec2 dist = halfwidth * a_extrude * scale;

    vec2 pos = floor(a_pos * 0.5);

    gl_Position = u_matrix * vec4(pos + dist, 0.0, 1.0);

    v_color = u_color;
}
