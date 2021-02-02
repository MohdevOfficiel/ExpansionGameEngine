#include "pch.h"
#include "RD_ShaderLoader.h"

#ifdef BUILD_OPENGL

RD_ShaderLoader_GL::RD_ShaderLoader_GL() {
	m_program_id = 0;
}

RD_ShaderLoader_GL::~RD_ShaderLoader_GL() {
	glUseProgram(0);
	glDeleteProgram(m_program_id);
}

void RD_ShaderLoader_GL::compileShaderFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
	if (!std::filesystem::exists(vertexShaderFile)) {
		dispErrorMessageBox(StrToWStr("Cannot open " + vertexShaderFile + " path does not exists."));
		return;
	}

	if (!std::filesystem::exists(fragmentShaderFile)) {
		dispErrorMessageBox(StrToWStr("Cannot open " + fragmentShaderFile + " path does not exists."));
		return;
	}

	//Common variables
	std::string vertexShaderData;
	std::string fragmentShaderData;

	const char* c_vertexShaderData;
	const char* c_fragmentShaderData;

	unsigned int vertexShader;
	unsigned int fragmentShader;

	int success;
	char infoLog[512];

	//Variable Initialization
	vertexShaderData = getFileData(vertexShaderFile);
	fragmentShaderData = getFileData(fragmentShaderFile);

	c_vertexShaderData = vertexShaderData.c_str();
	c_fragmentShaderData = fragmentShaderData.c_str();

	//Compiling vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &c_vertexShaderData, NULL);
	glCompileShader(vertexShader);

	//Get compiling error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		dispErrorMessageBox(TEXT("Vertex shader error, see console."));
		std::cerr << "GLSL Compile Error (Vertex shader) : " << infoLog << std::endl;
	}

	//Compiling fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &c_fragmentShaderData, NULL);
	glCompileShader(fragmentShader);

	//Get compiling error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		dispErrorMessageBox(TEXT("Fragment shader error, see console."));
		std::cerr << "GLSL Compile Error (Fragment shader) : " << infoLog << std::endl;
	}

	//Creating && Linking program
	m_program_id = glCreateProgram();
	//Linking
	glAttachShader(m_program_id, vertexShader);
	glAttachShader(m_program_id, fragmentShader);
	glLinkProgram(m_program_id);

	//Get linking errors
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_program_id, 512, NULL, infoLog);
		dispErrorMessageBox(TEXT("Error while linking program, see console."));
		std::cerr << "GLSL Linking Error : " << infoLog << std::endl;
	}

	//Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void RD_ShaderLoader_GL::CompileShaderFromCode(const std::string& vertexCode, const std::string& fragmentCode) {
	//Common variables
	const char* c_vertexShaderData;
	const char* c_fragmentShaderData;

	unsigned int vertexShader;
	unsigned int fragmentShader;

	int success;
	char infoLog[512];

	//Variable Initialization
	c_vertexShaderData = vertexCode.c_str();
	c_fragmentShaderData = fragmentCode.c_str();

	//Compiling vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &c_vertexShaderData, NULL);
	glCompileShader(vertexShader);

	//Get compiling error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		dispErrorMessageBox(TEXT("Vertex shader error, see console."));
		std::cerr << "GLSL Compile Error (Vertex shader) : " << infoLog << std::endl;
	}

	//Compiling fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &c_fragmentShaderData, NULL);
	glCompileShader(fragmentShader);

	//Get compiling error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		dispErrorMessageBox(TEXT("Fragment shader error, see console."));
		std::cerr << "GLSL Compile Error (Fragment shader) : " << infoLog << std::endl;
	}

	//Creating && Linking program
	m_program_id = glCreateProgram();
	//Linking
	glAttachShader(m_program_id, vertexShader);
	glAttachShader(m_program_id, fragmentShader);
	glLinkProgram(m_program_id);

	//Get linking errors
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_program_id, 512, NULL, infoLog);
		dispErrorMessageBox(TEXT("Error while linking program, see console."));
		std::cerr << "GLSL Linking Error : " << infoLog << std::endl;
	}

	//Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void RD_ShaderLoader_GL::useShader() {
	glUseProgram(m_program_id);
}

void RD_ShaderLoader_GL::SetBool(const std::string& name, bool value) {
	unsigned int uniLoc = glGetUniformLocation(m_program_id, name.c_str());

	glUniform1i(uniLoc, (int)value);
}

void RD_ShaderLoader_GL::SetInt(const std::string& name, int value) {
	unsigned int uniloc = glGetUniformLocation(m_program_id, name.c_str());

	glUniform1i(uniloc, value);
}

void RD_ShaderLoader_GL::SetFloat(const std::string& name, float value) {
	unsigned int uniloc = glGetUniformLocation(m_program_id, name.c_str());

	glUniform1f(uniloc, value);
}

void RD_ShaderLoader_GL::SetMatrix(const std::string& name, mat4f matrix) {
	unsigned int uniloc = glGetUniformLocation(m_program_id, name.c_str());

	glUniformMatrix4fv(uniloc, 1, GL_TRUE, matrix.GetPTR());
}

void RD_ShaderLoader_GL::SetVec3(const std::string& name, vec3f vec) {
	unsigned int uniloc = glGetUniformLocation(m_program_id, name.c_str());

	//glUniform3f(uniloc, vec.getX(), vec.getY(), vec.getZ());
	glUniform3fv(uniloc, 1, vec.GetPTR());
}

unsigned int RD_ShaderLoader_GL::GetProgID() {
	return m_program_id;
}

#endif //BUILD_OPENGL

#ifdef BUILD_VULKAN

#include "RD_RenderingAPI_Vk.h"

RD_ShaderLoader_Vk::RD_ShaderLoader_Vk(RD_RenderingAPI_Vk* api) {
	m_api = api;

	m_pl_st_cInfo[0] = VkPipelineShaderStageCreateInfo{};
	m_pl_st_cInfo[1] = VkPipelineShaderStageCreateInfo{};
}

RD_ShaderLoader_Vk::~RD_ShaderLoader_Vk() {
	m_api->DestroyShaderModule(m_shader_frag);
	m_api->DestroyShaderModule(m_shader_vert);
}

void RD_ShaderLoader_Vk::compileShaderFromFile(const std::string& vert, const std::string& frag) {
	if (!std::filesystem::exists(vert)) {
		dispErrorMessageBox(StrToWStr("Cannot open " + vert + " path does not exists."));
		return;
	}

	if (!std::filesystem::exists(frag)) {
		dispErrorMessageBox(StrToWStr("Cannot open " + frag + " path does not exists."));
		return;
	}

	std::ifstream vFile;
	vFile.open(vert, std::ios::ate | std::ios::binary);
	if (!vFile.is_open()) {
		std::cerr << "ERROR: Cannot open file " << vert << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot open file" + vert));
		return;
	}

	size_t vfSize = vFile.tellg();
	std::vector<char> vertContent(vfSize);

	vFile.seekg(0);
	vFile.read(vertContent.data(), vfSize);
	vFile.close();

	std::ifstream fFile;
	fFile.open(frag, std::ios::ate | std::ios::binary);
	if (!fFile.is_open()) {
		std::cerr << "ERROR: Cannot open file " << frag << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot open file" + frag));
		return;
	}

	size_t ffSize = fFile.tellg();
	std::vector<char> fragContent(ffSize);

	fFile.seekg(0);
	fFile.read(fragContent.data(), ffSize);
	fFile.close();

	m_shader_vert = m_api->CreateShaderModule(vertContent);
	m_shader_frag = m_api->CreateShaderModule(fragContent);

	VkPipelineShaderStageCreateInfo vertStage_cInfo{};
	vertStage_cInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertStage_cInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertStage_cInfo.module = m_shader_vert;
	vertStage_cInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragStage_cInfo{};
	fragStage_cInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragStage_cInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragStage_cInfo.module = m_shader_frag;
	fragStage_cInfo.pName = "main";

	m_pl_st_cInfo[0] = vertStage_cInfo;
	m_pl_st_cInfo[1] = fragStage_cInfo;
}

void RD_ShaderLoader_Vk::CompileShaderFromCode(const std::string& vert, const std::string& frag) {
	/* . . . SHADER LOADING . . . */

	VkPipelineShaderStageCreateInfo vertStage_cInfo{};
	vertStage_cInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertStage_cInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertStage_cInfo.module = m_shader_vert;
	vertStage_cInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragStage_cInfo{};
	fragStage_cInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragStage_cInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragStage_cInfo.module = m_shader_frag;
	fragStage_cInfo.pName = "main";

	m_pl_st_cInfo[0] = vertStage_cInfo;
	m_pl_st_cInfo[1] = fragStage_cInfo;
}

void RD_ShaderLoader_Vk::useShader() {

}

void RD_ShaderLoader_Vk::SetBool(const std::string& name, const bool value) {

}

void RD_ShaderLoader_Vk::SetInt(const std::string& name, const int value) {

}

void RD_ShaderLoader_Vk::SetFloat(const std::string& name, const float value) {

}

void RD_ShaderLoader_Vk::SetMatrix(const std::string& name, const mat4f matrix) {

}

void RD_ShaderLoader_Vk::SetVec3(const std::string& name, const vec3f vec) {

}

#endif //BUILD_VULKAN