#version 450 core
layout (location = 0) out vec4 LightPass;

layout (location = 3) in vec2 UVcoords;

//uniform sampler2D GUIscreen;

//Passes
layout (binding=0) uniform sampler2D ShadowPass;
layout (binding=1) uniform sampler2D gPos;
layout (binding=2) uniform sampler2D gNormal;
layout (binding=3) uniform sampler2D gAlbedo;
layout (binding=4) uniform sampler2D gSpec;

//Ambient
layout (binding=5) uniform Ambient {
	float AmbientStrength;
	vec3 AmbientColor;
};

//Point Light
const int MAX_POINT_LIGHTS = 243;

layout (binding=6) uniform PointLights {
	vec3 LightPos[MAX_POINT_LIGHTS];
	float LightBrightness[MAX_POINT_LIGHTS];
	vec3 LightColor[MAX_POINT_LIGHTS];
	float LightRadius[MAX_POINT_LIGHTS];
	int nbrPointLight;
};

//Dir Light
layout (binding=7) uniform DirLights {
	int nbrDirLight;
	vec3 DirLightDir[10];
	vec3 DirLightColor[10];
	float DirLightBrightness[10];
};

layout (binding=8) uniform Camera { vec3 CamPos; };

layout (binding=9) uniform Features {
	bool ftr_lighting;
	bool ftr_specular;
	bool ftr_ambient;
};

vec3 norm = normalize(texture(gNormal, UVcoords).rgb);
vec3 FragPos = texture(gPos, UVcoords).rgb;

vec3 Diffuse = texture(gAlbedo, UVcoords).rgb;
float Specular = texture(gAlbedo, UVcoords).a;
float SpecularExp = texture(gSpec, UVcoords).r;

vec3 viewDir = normalize(CamPos - FragPos);

vec3 CalcDirLight(int index) {
	vec3 dir = normalize(vec3(-DirLightDir[index]));

	//Diffuse
	float diff = max(0.0, dot(norm, dir));
	vec3 diffuse = (diff * DirLightBrightness[index] * DirLightColor[index]);

	//Specular
	vec3 d_specular = vec3(0.0);
	if(ftr_specular) {
		vec3 reflectDir = reflect(-dir, norm);

		float spec = pow(max(0.0, dot(viewDir, reflectDir)), SpecularExp);

		d_specular = spec * DirLightColor[index] * DirLightBrightness[index] * Specular;
	}

	return diffuse + d_specular;
}

vec3 CalcPointLight(int lightIndex) {
	float dist = length(LightPos[lightIndex] - FragPos);
	if(dist < LightRadius[lightIndex]) {
		//Diffuse
		vec3 LightDir = normalize(LightPos[lightIndex] - FragPos);
		float attenuation = (1.0 / (1.0 + 0.7 * (dist * dist)));

		float diffuse = LightBrightness[lightIndex] * max(0.0, dot(norm, LightDir)) / dist;

		//Specular
		vec3 specular = vec3(0.0, 0.0, 0.0);

		if(ftr_specular) {
			vec3 reflectDir = reflect(-LightDir, norm);

			vec3 hwDir = normalize(LightDir + viewDir);
			float spec = pow(max(0.0, dot(norm, hwDir)), SpecularExp);

			specular = (spec * LightColor[lightIndex] * Specular);
		}

		return attenuation * (LightColor[lightIndex] * (diffuse + specular));
	} else {
		return vec3(0.0);
	}
}

void main() {
	if(!ftr_lighting) {
		LightPass = texture(gAlbedo, UVcoords);
		return;
	}

	vec3 diffSpec = vec3(0.0);

	float shadow = texture(ShadowPass, UVcoords).r;

	for(int i = 0; i < nbrDirLight; i++) {
		diffSpec += CalcDirLight(i) * shadow;
	}

	for(int i = 0; i < nbrPointLight; i++) {
		diffSpec += CalcPointLight(i);
	}

	vec3 ambient = AmbientColor * AmbientStrength;
	vec3 result = (diffSpec + ambient);

	vec4 gamma = vec4(1.0 / 2.2);

	vec4 render = clamp(pow(vec4(Diffuse, 1.0) * vec4(result, 1.0), gamma), 0.0, 1.0);
	render.a = 1.0;

	LightPass = render;
}