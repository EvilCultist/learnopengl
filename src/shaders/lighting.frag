#version 330 core

out vec4 fragColor;

uniform vec3 ambientLight;
uniform vec3 baseColor;

void main() {
    fragColor = vec4(ambientLight * baseColor, 1.0);
}
