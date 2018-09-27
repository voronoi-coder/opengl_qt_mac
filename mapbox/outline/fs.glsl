//#version 410

uniform vec4 u_outline_color;
uniform vec2 u_screen;

varying vec2 v_pos;

//out vec4 color;

void main() {
    float dist = length(v_pos - gl_FragCoord.xy);
    float alpha = 1.0 - smoothstep(0.0, 2.0, dist);

    gl_FragColor = u_outline_color * alpha;
}
