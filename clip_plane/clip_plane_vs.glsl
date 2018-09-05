#version 330

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;

uniform mat4 u_mvpmatrix;
uniform mat4 u_mmatrix;

uniform vec3 u_light_pos;
uniform vec3 u_camera;
uniform vec4 u_clip_plane;

out vec4 ambient;
out vec4 diffuse;
out vec4 specular;
out float clip_distance;

void pointLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular,
                in vec3 lightLocation, in vec4 lightAmbient, in vec4 lightDiffuse, in vec4 lightSpecular){
    ambient = lightAmbient;

    vec3 normalTarget = a_pos + normal;
    vec3 newNormal = (u_mmatrix * vec4(normalTarget, 1.0)).xyz - (u_mmatrix * vec4(a_pos, 1.0)).xyz;
    newNormal = normalize(newNormal);

    vec3 eyeDirection = normalize(u_camera - (u_mmatrix * vec4(a_pos, 1.0)).xyz);
    vec3 lightDirection = normalize(lightLocation - (u_mmatrix * vec4(a_pos, 1.0)).xyz);

    vec3 halfVector = normalize(lightDirection + eyeDirection);

    float shininess = 50.0;
    float diffuseFactor = max(0.0, dot(newNormal, lightDirection));
    float specularFactor = max(0.0, dot(newNormal, halfVector));
    specularFactor = (specularFactor == 0.0 ? 0.0 : pow(specularFactor, shininess));

    diffuse = lightDiffuse * diffuseFactor;
    specular = lightSpecular * specularFactor;
}


void main() {
    gl_Position = u_mvpmatrix * vec4(a_pos, 1.0);

    pointLight(normalize(a_normal), ambient, diffuse, specular, u_light_pos, vec4(0.1, 0.1, 0.1, 1.0),
    vec4(0.7,0.7,0.7,1.0), vec4(0.3,0.3,0.3,1.0));

    clip_distance = dot(a_pos.xyz, u_clip_plane.xyz) + u_clip_plane.w;
}
