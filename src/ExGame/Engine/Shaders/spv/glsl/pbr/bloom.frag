#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec3 bloom;

layout (location = 3) in vec2 UVcoords;

layout (binding = 0) uniform sampler2D gShaded;

layout (push_constant) uniform DATA {
    uniform bool horizontal;
    uniform int threshold;
};

int kernelSize = 25;
float ksize = 25;

float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
    vec3 result = texture(gShaded, UVcoords).rgb * weight[0];
    vec2 tex_offset = 1.0 / textureSize(gShaded, 0);

    vec2 texelSize = 1.0 / textureSize(gShaded, 0);

    if(horizontal) {
        for(int i = 1; i < 5; i++) {
            result += clamp(texture(gShaded, UVcoords + vec2(tex_offset.x * i, 0.0)).rgb - threshold, 0, 1) * weight[i];
            result += clamp(texture(gShaded, UVcoords - vec2(tex_offset.x * i, 0.0)).rgb - threshold, 0, 1) * weight[i];
        }
        bloom = clamp(result, 0, 1);
    } else {
        for(int i = 1; i < 5; i++) {
            result += clamp(texture(gShaded, UVcoords + vec2(0.0, tex_offset.y * i)).rgb - threshold, 0, 1) * weight[i];
            result += clamp(texture(gShaded, UVcoords - vec2(0.0, tex_offset.y * i)).rgb - threshold, 0, 1) * weight[i];
        }
        bloom = clamp(result, 0, 1);
    }
}