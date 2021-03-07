#version 450 core
layout (location = 1) out vec3 ssr_color;

layout (location = 3) in vec2 UVcoords;

layout (binding = 0) uniform sampler2D gPos;
layout (binding = 1) uniform sampler2D gNorm;
layout (binding = 2) uniform sampler2D ShadedImg;
layout (binding = 3) uniform sampler2D gMetRoughAO;
layout (binding = 4) uniform sampler2D Depth;

layout(std140, binding = 0) uniform CAMERA {
    mat4 projection;
    mat4 view;
};

layout(std140, binding = 5) uniform CameraData { 
    vec3 camPos;
};

void main() {
    discard;
}