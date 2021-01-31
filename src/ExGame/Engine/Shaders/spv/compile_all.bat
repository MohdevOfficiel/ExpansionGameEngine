set compilerPath="C:\VulkanSDK\1.2.162.1\Bin\glslc.exe"

%compilerPath% glsl/Beauty.frag -o frag/Beauty.spv
%compilerPath% glsl/Beauty.vert -o vert/Beauty.spv

%compilerPath% glsl/Debug.frag -o frag/Debug.spv
%compilerPath% glsl/Debug.vert -o vert/Debug.spv

%compilerPath% glsl/Light.frag -o frag/Light.spv
%compilerPath% glsl/Light.vert -o vert/Light.spv

%compilerPath% glsl/Shadow.frag -o frag/Shadow.spv
%compilerPath% glsl/Shadow.vert -o vert/Shadow.spv

%compilerPath% glsl/ShadowCalc.frag -o frag/ShadowCalc.spv
%compilerPath% glsl/ShadowCalc.vert -o vert/ShadowCalc.spv

%compilerPath% glsl/pbr/bloom.frag -o frag/pbr/bloom.spv
%compilerPath% glsl/pbr/bloom.vert -o vert/pbr/bloom.spv

%compilerPath% glsl/pbr/Light.frag -o frag/pbr/Light.spv
%compilerPath% glsl/pbr/Light.vert -o vert/pbr/Light.spv

%compilerPath% glsl/pbr/SSAO_Blur.frag -o frag/pbr/SSAO_Blur.spv
%compilerPath% glsl/pbr/SSAO_Blur.vert -o vert/pbr/SSAO_Blur.spv

%compilerPath% glsl/pbr/SSAO.frag -o frag/pbr/SSAO.spv
%compilerPath% glsl/pbr/SSAO.vert -o vert/pbr/SSAO.spv

%compilerPath% glsl/pbr/SSR.frag -o frag/pbr/SSR.spv
%compilerPath% glsl/pbr/SSR.vert -o vert/pbr/SSR.spv