#version 450 core
#extension GL_ARB_bindless_texture : enable
layout (location = 0) out vec3 bloom;

in vec2 UVcoords;

#ifdef GL_ARB_bindless_texture
    layout(std430, binding = 8) buffer BINDLESS_PASSES {
        sampler2D passes[6];
    };

    layout(std430, binding = 12) buffer BINDLESS_FINAL_PASSES {
        sampler2D fpasses[4];
    };
#else
    uniform sampler2D gShaded;
#endif //GL_ARB_bindless_texture

layout(std430, binding = 10) buffer BLUR_STATE {
	vec3 dir;
	int index;
    int threshold;
    bool first_pass;
};

//From https://github.com/Jam3/glsl-fast-gaussian-blur/blob/master/13.glsl
vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  color += (texture2D(image, uv) - threshold) * 0.1964825501511404;
  color += texture2D(image, uv + (off1 / resolution)) * 0.2969069646728344;
  color += texture2D(image, uv - (off1 / resolution)) * 0.2969069646728344;
  color += texture2D(image, uv + (off2 / resolution)) * 0.09447039785044732;
  color += texture2D(image, uv - (off2 / resolution)) * 0.09447039785044732;
  color += texture2D(image, uv + (off3 / resolution)) * 0.010381362401148057;
  color += texture2D(image, uv - (off3 / resolution)) * 0.010381362401148057;
  return color;
}

void main() {
    if(first_pass) {
        #ifndef GL_ARB_bindless_texture
	        bloom = clamp(blur13(gShaded, UVcoords, textureSize(gShaded, 0), dir.xy).rgb - threshold, 0, 1);
	    #else
	        bloom = clamp(blur13(passes[index], UVcoords, textureSize(passes[index], 0), dir.xy).rgb - threshold, 0, 1);
        #endif
    } else {
        #ifndef GL_ARB_bindless_texture
	        bloom = clamp(blur13(gShaded, UVcoords, textureSize(gShaded, 0), dir.xy).rgb - threshold, 0, 1);
	    #else
	        bloom = clamp(blur13(fpasses[index], UVcoords, textureSize(fpasses[index], 0), dir.xy).rgb - threshold, 0, 1);
        #endif
    }
}