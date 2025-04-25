#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 rotation;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 lightPos;

out vec3 pos;
out vec3 normal;
out vec3 lightLoc;

void main() {
    // model = model * rotation;
    pos = vec3(model * rotation * vec4(aPos, 1.0));
    // gl_Position = proj * view * model * vec4(aPos, 1.0);
    gl_Position = proj * view * vec4(pos, 1.0);
    lightLoc = lightPos;
    // normal = vec3(1.0, 1.0, 1.0);
    // normal = vec3(transpose(rotation) * vec4(aNormal, 1.0));
    normal = vec3(rotation * vec4(aNormal, 1.0));
}
