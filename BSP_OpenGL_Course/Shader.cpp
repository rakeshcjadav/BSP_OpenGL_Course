#include"Shader.h"
#include<string>
#include<fstream>
#include"OpenGL.h"
#include"WinUtils.h"
#include"Log.h"
#include<regex>

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
			LOG_ERROR << "SHADER::"<< shaderType <<"::COMPILATION_FAILED";
			LOG_ERROR << infoLog;
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
	//LOG_INFO << "Loading Shader : " << shaderFile << LOG_END;
	string shaderSource;
	if (file.is_open())
	{
		string line;
		std::regex reg("[ ]*#include[ ]*\"(.*)\"");
		while (getline(file, line))
		{
			std::smatch matches;
			// search and include reference shader file
			if (std::regex_search(line, matches, reg))
			{
				shaderSource += LoadShader(matches.str(1));
			}
			else
			{
				shaderSource += line + "\n";
			}
		}
	}

	file.close();
	return shaderSource;
}