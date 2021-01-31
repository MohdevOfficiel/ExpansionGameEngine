#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 3) in vec2 UVcoords;

layout (binding = 1) uniform sampler2D lightpass;
layout (binding = 2) uniform sampler2D GUIscreen;

layout (binding = 3) uniform sampler2D bloom;
layout (binding = 4) uniform sampler2D SSR;

void main() {
    vec4 gui = texture(GUIscreen, UVcoords);

    //FragColor = mix(texture(lightpass, UVcoords), gui, gui.a);

    vec4 lightSSR = clamp(texture(lightpass, UVcoords), 0, 1) + (texture(bloom, UVcoords) * 2);

    FragColor = mix(lightSSR, gui, gui.a);
}