#version 450 core
layout (location = 0) in vec3 aPos;

layout(binding = 0) uniform MatrixData {
	mat4 lightproj;
	mat4 lightview;
	mat4 model;
};

void main() {
	gl_Position = lightproj * lightview * model * vec4(aPos, 1.0);
}