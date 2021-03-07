#version 410 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aUV;

layout (location = 1) out vec2 UVcoords;

void main() {
	UVcoords = aUV;
	gl_Position = vec4(aPos, 1.0);
}
