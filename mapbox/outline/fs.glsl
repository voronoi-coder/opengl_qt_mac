#version 410

uniform vec4 u_outline_color;

in vec2 v_pos;

out vec4 color;

void main() {
    float dist = length(v_pos - gl_FragCoord.xy);
    float alpha = 1.0 - smoothstep(0.0, 0.01, dist);

    color = u_outline_color;
}
