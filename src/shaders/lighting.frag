#version 330 core

in vec3 pos;
in vec3 normal;

uniform vec3 ambientLight;
uniform vec3 baseColor;
uniform vec3 lightPos;

out vec4 fragColor;

void main() {
    vec3 ambient = ambientLight * 0.1;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ambientLight;
    vec3 result = (ambient + diffuse) * baseColor;
    fragColor = vec4(result, 1.0);
}
