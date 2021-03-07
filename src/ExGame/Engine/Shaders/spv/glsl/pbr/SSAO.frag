#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out float ssao;

layout (location = 3) in vec2 UVcoords;

layout (binding = 0) uniform sampler2D gPos;
layout (binding = 1) uniform sampler2D gNorm;
layout (binding = 2) uniform sampler2D noise;

layout(std140, binding = 0) uniform CAMERA {
    mat4 projection;
    mat4 view;
};

layout(std140, binding = 6) uniform SSAO_Data {
    int scr_w;
    int scr_h;

    vec3 samples[64];
};

float radius = 0.5;
float bias = 0.05;

vec2 noiseScale = vec2(scr_w / 4.0, scr_h / 4.0);

mat4 tview = transpose(view);
mat4 tproj = transpose(projection);

void main() {
    vec3 FragPos = vec4(tview * texture(gPos, UVcoords)).xyz;
    vec3 norm = texture(gNorm, UVcoords).xyz;
    vec3 randomVec = normalize(texture(noise, UVcoords * noiseScale).xyz);

    vec3 tangent = normalize(randomVec - norm * dot(randomVec, norm));
    vec3 bitangent = cross(norm, tangent);
    mat3 TBN = mat3(tangent, bitangent, norm);

    float occlusion = 0.0;
    for(int i = 0; i < 64; i++) {
        vec3 samplePos = TBN * samples[i];
        samplePos = samplePos * radius + FragPos;

        vec4 offset = vec4(samplePos, 1.0);
        offset = tproj * offset;
        offset.xy /= offset.w;
        offset.xy = offset.xy * 0.5 + 0.5;

        float sampleDepth = vec4(tview * texture(gPos, offset.xy)).z;

        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(FragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;
    }

    occlusion = 1.0 - (occlusion / 64.0);
    ssao = occlusion;
}