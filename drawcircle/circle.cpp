#include "circle.hpp"

namespace mdgl {
namespace shaders {

const char* circle::name = "circle";
const char* circle::vertexSource = R"MDGL_SHADER(

uniform mat4 u_matrix;
attribute vec2 a_pos;

uniform highp vec4 u_color;
uniform mediump float u_radius;


varying vec3 v_data;

void main(void) {

    highp vec4 color = u_color;
    mediump float radius = u_radius;

    // unencode the extrusion vector that we snuck into the a_pos vector
    vec2 extrude = vec2(mod(a_pos, 2.0) * 2.0 - 1.0);

    // multiply a_pos by 0.5, since we had it * 2 in order to sneak
    // in extrusion data
    vec2 circle_center = floor(a_pos * 0.5);
    gl_Position = u_matrix * vec4(circle_center + extrude * (radius), 0, 1);

    v_data = vec3(extrude.x, extrude.y, 1.0);
}

)MDGL_SHADER";
const char* circle::fragmentSource = R"MDGL_SHADER(

uniform highp vec4 u_color;
uniform mediump float u_radius;

varying vec3 v_data;

void main() {

    highp vec4 color = u_color;


    mediump float radius = u_radius;


    vec2 extrude = v_data.xy;
    float extrude_length = length(extrude);

    float opacity_t = step(-1.0, -extrude_length);
    float opacity_t2 = smoothstep(0.0, -0.3, extrude_length - 1.0);

    gl_FragColor = color * opacity_t2;

#ifdef OVERDRAW_INSPECTOR
    gl_FragColor = vec4(1.0);
#endif
}

)MDGL_SHADER";

} // namespace shaders
} // namespace mdgl

