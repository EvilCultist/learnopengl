#version 150 core

// uniform vec3 triangleColor;
in vec3 Color;
in vec2 TexCord;

out vec4 outColor;
uniform sampler2D texMask;
uniform sampler2D texGlass;

void main() {
    // outColor = texture(tex, TexCord) * vec4(Color, 1.0);
    vec4 mask = texture(texMask, TexCord); // * vec4(Color, 1.0);
    vec4 glass = texture(texGlass, TexCord);
    outColor = mix(glass, mask, 0.5);
    outColor = mix(glass, mask, 0.5) * vec4(Color, 1.0);
}
