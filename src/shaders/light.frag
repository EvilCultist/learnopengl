#version 330 core

out vec4 fragColor;

uniform vec3 ambientLight;

void main() {
    fragColor = vec4(ambientLight, 1.0);
}
