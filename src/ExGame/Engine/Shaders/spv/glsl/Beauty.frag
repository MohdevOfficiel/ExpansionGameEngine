#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 3) in vec2 UVcoords;

layout (binding = 8) uniform sampler2D lightpass;
layout (binding = 9) uniform sampler2D GUIscreen;

layout (binding = 12) uniform sampler2D bloom;
layout (binding = 11) uniform sampler2D SSR;

out vec4 FragColor;

void main() {
    vec4 gui = texture(GUIscreen, UVcoords);

    //FragColor = mix(texture(lightpass, UVcoords), gui, gui.a);

    vec4 lightSSR = clamp(texture(lightpass, UVcoords), 0, 1) + (texture(bloom, UVcoords) * 2);

    FragColor = mix(lightSSR, gui, gui.a);
}