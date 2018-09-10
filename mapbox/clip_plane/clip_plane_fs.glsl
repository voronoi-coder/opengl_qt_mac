#version 330

in vec4 ambient;
in vec4 diffuse;
in vec4 specular;
in float clip_distance;

out vec4 fcolor;

void main() {
    if(clip_distance < 0.0) discard;

    vec4 finalColor = vec4(0.95, 0.95, 0.95, 1.0);
    fcolor = finalColor * ambient + finalColor * specular + finalColor * diffuse;
}
