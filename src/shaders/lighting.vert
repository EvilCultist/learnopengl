#version 330 core

in vec3 aPos;
in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 pos;
out vec3 normal;

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    normal = aNormal;
    pos = aPos;
}
