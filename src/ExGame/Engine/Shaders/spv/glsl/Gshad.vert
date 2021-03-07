#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

layout (location = 3) out vec3 Normal;

layout (location = 4) out vec3 FragPos;
layout (location = 5) out vec2 UVcoord;

layout(std140, binding = 0) uniform CAMERA {
    mat4 projection;
    mat4 view;
};

layout(binding = 8) uniform MODEL {
    uniform mat4 model;
}

void main()
{
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    FragPos = vec3(model * vec4(aPos, 1.0));
    UVcoord = aUV;

    gl_Position = transpose(projection) * transpose(view) * vec4(FragPos, 1.0);
}