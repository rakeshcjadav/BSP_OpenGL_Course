#include"Shader.h"
#include<string>
#include<fstream>
#include"OpenGL.h"
#include"WinUtils.h"
#include"Log.h"
#include<format>

using namespace std;

CShader::CShader(SHADER_TYPE type, std::string shaderFile)
{
	std::string shaderType;
	if(type == VERTEX)
	{
		m_IDShader = glCreateShader(GL_VERTEX_SHADER);
		shaderType = "VERTEX";
	}
	else
	{
		m_IDShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderType = "FRAGMENT";
	}

	std::string shader = LoadShader(shaderFile);
	const char * shaderSource = shader.c_str();

	glShaderSource(m_IDShader, 1, &shaderSource, NULL);
	glCompileShader(m_IDShader);
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(m_IDShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_IDShader, 512, NULL, infoLog);
			LogMessage(std::format("ERROR::SHADER::{0}::COMPILATION_FAILED", shaderType));
			LogMessage(infoLog);
		}
	}
}

CShader::~CShader()
{
	glDeleteShader(m_IDShader);
}

unsigned int CShader::GetID()
{
	return m_IDShader;
}

std::string CShader::LoadShader(std::string shaderFile)
{
	// All shaders are put in specific folder
	string shaderFilePath = GetShaderPath();

	ifstream file(shaderFilePath.append(shaderFile));
	string shaderSource;
	if (file.is_open())
	{
		string line;
		int lineNumber = 0;
		while (getline(file, line))
		{
			shaderSource += line + "\n";
		}
	}

	file.close();
	return shaderSource;
}