#include"pch.h"
#include"Shader.h"

using namespace std;


CShader::CShader(SHADER_TYPE type, std::string shaderSource)
{
	std::string shaderType;
	if(type == SHADER_TYPE::VERTEX)
	{
		m_IDShader = glCreateShader(GL_VERTEX_SHADER);
		shaderType = "VERTEX";
	}
	else
	{
		m_IDShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderType = "FRAGMENT";
	}

	m_strSource = shaderSource;
	const char * source = shaderSource.c_str();

	glShaderSource(m_IDShader, 1, &source, NULL);
	glCompileShader(m_IDShader);
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(m_IDShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_IDShader, 512, NULL, infoLog);
			LOG_ERROR << "SHADER::"<< shaderType <<"::COMPILATION_FAILED" << LOG_END;;
			LOG_ERROR << infoLog;
		}
	}
}

CShader::~CShader()
{
	glDeleteShader(m_IDShader);
}

unsigned int CShader::GetID() const
{
	return m_IDShader;
}

void CShader::Print() const
{
	std::stringstream stream(m_strSource);
	std::string line;
	int i = 0;
	while(std::getline(stream, line))
	{
		LOG_INFO << i++ <<": " << line << LOG_END;
	}
	std::cout << flush;
	//LOG_ERROR << m_strSource << std::endl;
}