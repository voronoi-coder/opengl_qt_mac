#version 330

in vec4 v_color;
in vec2 v_normal;

out vec4 color;

void main() {
    float alpha = length(v_normal) > 1.0 ? 0.0:1.0;
    color = v_color * alpha;
}
