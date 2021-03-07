#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 aPos;

layout (push_constant) uniform LIGHTDATA {
	uniform mat4 lightproj;
	uniform mat4 lightview;
};

layout (std140, binding = 7) uniform MODEL {
	uniform mat4 model;
};

void main() {
	gl_Position = lightproj * lightview * model * vec4(aPos, 1.0);
}