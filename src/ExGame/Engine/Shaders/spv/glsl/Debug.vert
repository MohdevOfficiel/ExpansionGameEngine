#version 450 core
layout (location = 0) in vec3 aPos;

layout (binding = 0) uniform MatrixData {
    mat4 projection;
    mat4 view;
    mat4 model;
} matrixData;

void main()
{
    vec3 FragPos = vec3(matrixData.model * vec4(aPos, 1.0));

    gl_Position = matrixData.projection * matrixData.view * vec4(FragPos, 1.0);
}