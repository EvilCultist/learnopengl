#version 330 core

float ambientStrenght = 0.1;
float spec_str = 0.5;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

in vec3 pos;
in vec3 normal;

uniform vec3 viewPos;
uniform vec3 lightPos;

out vec4 fragColor;

void main() {
    vec3 ambient = material.ambient * ambientStrenght;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - pos);
    vec3 viewDir = normalize(viewPos - pos);

    vec3 reflDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflDir), 0.0), 128 * material.shininess);
    vec3 specular = spec * spec_str * material.specular;

    // if (dot(viewDir, reflDir) > 0.0) {
    //     fragColor = vec4(ambientLight, 1.0);
    //     return;
    // }

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse;

    vec3 result = (ambient + diffuse + specular);
    fragColor = vec4(result, 1.0);
}

//
