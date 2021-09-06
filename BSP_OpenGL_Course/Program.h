#pragma once
#include<string>
#include"GLM.h"

// Forward declarations
class CShader;

class CProgram
{
public:
	CProgram(std::string strVertexShaderFile, std::string strFragmentShaderFile);

	void Use();
	void SetUniform(std::string name, int value);
	void SetUniform(std::string name, float value);
	void SetUniform(std::string name, glm::vec3 & value);
	void SetUniform(std::string name, glm::vec4 & value);
	void SetUniform(std::string name, glm::mat4 & value);
	void SetUniform(std::string name, float * value);
private:
	void AttachShader(CShader* pShader);
	void LinkProgram();
private:
	unsigned int m_IDProgram;
};