#include"Program.h"
#include"Shader.h"
#include"OpenGL.h"
#include"Log.h"

CProgram::CProgram(std::string strVertexShaderFile, std::string strFragmentShaderFile)
{
	CShader* pShaderVS = new CShader(CShader::SHADER_TYPE::VERTEX, strVertexShaderFile);
	CShader* pShaderFS = new CShader(CShader::SHADER_TYPE::FRAGMENT, strFragmentShaderFile);

    m_IDProgram = glCreateProgram();
    AttachShader(pShaderVS);
    AttachShader(pShaderFS);
    LinkProgram();

    delete pShaderVS;
    delete pShaderFS;
}

void CProgram::Use()
{
    glUseProgram(m_IDProgram);
}

void CProgram::SetUniform(std::string name, int value)
{
    glUniform1i(glGetUniformLocation(m_IDProgram, name.c_str()), value);
}

void CProgram::SetUniform(std::string name, float value)
{
    glUniform1f(glGetUniformLocation(m_IDProgram, name.c_str()), value);
}

void CProgram::SetUniform(std::string name, glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, glm::value_ptr(value));
}

void CProgram::SetUniform(std::string name, glm::vec4 & value)
{
    glUniform4fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, glm::value_ptr(value));
}

void CProgram::SetUniform(std::string name, glm::mat4 & value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void CProgram::SetUniform(std::string name, float* value)
{
    glUniform4fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, value);
}

void CProgram::AttachShader(CShader* pShader)
{
    glAttachShader(m_IDProgram, pShader->GetID());
}

void CProgram::LinkProgram()
{
    glLinkProgram(m_IDProgram);
    {
        int  success;
        char infoLog[512];
        glGetProgramiv(m_IDProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_IDProgram, 512, NULL, infoLog);
            std::cout << "PROGRAM::LINKING_FAILED";
            std::cout << infoLog;
        }
    }
}