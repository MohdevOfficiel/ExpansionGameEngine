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