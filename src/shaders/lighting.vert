#version 330 core

in vec3 aPos;
// in vec3 aNormal;

uniform vec3 aNormal;

uniform mat4 model;
uniform mat4 rotation;
uniform mat4 view;
uniform mat4 proj;

out vec3 pos;
out vec3 normal;

void main() {
    // model = model * rotation;
    pos = vec3(model * rotation * vec4(aPos, 1.0));
    // gl_Position = proj * view * model * vec4(aPos, 1.0);
    gl_Position = proj * view * vec4(pos, 1.0);
    // normal = vec3(1.0, 1.0, 1.0);
    normal = aNormal;
}
