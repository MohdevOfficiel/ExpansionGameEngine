#version 450 core

layout (binding = 1) uniform Color {
	vec3 debugColor;
} color;

layout (location = 0) out vec3 FragColor;

void main() {
	FragColor = vec3(1.0, 1.0, 1.0);
}