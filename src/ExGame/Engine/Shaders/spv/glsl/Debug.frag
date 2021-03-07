#version 450 core
#extension GL_ARB_separate_shader_objects : enable

vec3 debugColor = vec3(1.0, 1.0, 1.0);

layout (location = 0) out vec3 FragPos;

void main() {
	FragPos = debugColor;
}