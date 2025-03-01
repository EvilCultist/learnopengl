
#version 330 core

out vec4 fragColor;

uniform vec3 lightColor;

void main() {
    fragColor = vec4(lightColor, 1.0);
    // fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
