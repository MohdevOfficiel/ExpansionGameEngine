#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec3 ShadowColor;

layout (location = 3) in vec2 UVcoords;

layout(push_constant) uniform DATA {
	uniform mat4 lspaceMat[10];
	uniform int NbrDirLights;
};

layout (binding = 0) uniform sampler2D ShadowMap[10];

layout (binding = 1) uniform sampler2D gPos;

void main() {
	float finalShadow = 0.0;

	for(int i = 0; i < NbrDirLights; i++) {
		vec4 fpls = lspaceMat[i] * vec4(texture(gPos, UVcoords).rgb, 1.0);

		vec3 projCoords = fpls.xyz / fpls.w;
		projCoords = projCoords * 0.5 + 0.5;

		if(projCoords.z > 1.0) {
			ShadowColor = vec3(0.0, 0.0, 0.0);
		}

		float closestDepth = texture(ShadowMap[i], projCoords.xy).r;
		float currentDepth = projCoords.z;

		float bias = 0.0015;

		float shadow = 0.0;

		vec2 texelSize = 1.0 / textureSize(ShadowMap[i], 0);
		for(float x = -1; x <= 1; x += 1) {
			for(float y = -1; y <= 1; y += 1) {
				float pcfDepth = texture(ShadowMap[i], projCoords.xy + vec2(x, y) * texelSize).r;

				shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
			}
		}

		finalShadow += clamp(shadow / 9, 0, 1);
	}


	ShadowColor = vec3(1 - finalShadow, 0.0, 0.0);
	//ShadowColor = fpls.rgb;
}