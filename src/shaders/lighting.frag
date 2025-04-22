#version 330 core

in vec3 pos;
in vec3 normal;

uniform vec3 ambientLight;
uniform vec3 baseColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

float spec_str = 0.8;

out vec4 fragColor;

void main() {
    // vec3 normal = vec3(1.0, 0, 0);
    vec3 ambient = ambientLight * 0.2;

    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(lightPos - pos);
    vec3 viewDir = normalize(viewPos - pos);
    vec3 reflDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflDir), 0), 32);
    vec3 specular = spec * spec_str * ambientLight;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ambientLight;

    vec3 result = (ambient + diffuse + specular) * baseColor;
    // vec3 result = ambient * baseColor;
    fragColor = vec4(result, 1.0);
}
