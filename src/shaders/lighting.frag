#version 330 core

out vec4 fragColor;

uniform vec3 lightColor;
uniform vec3 baseColor;

void main() {
    vec3 ambient = lightColor * 1.0;
    vec3 result = ambient * baseColor;
    fragColor = vec4(result, 1.0);
    // fragColor = vec4(baseColor, 1.0);
}
