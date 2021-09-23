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

    /*
    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 128; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(m_IDProgram, GL_ACTIVE_UNIFORMS, &count);

    std::cout << std::endl << count << std::endl;

    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(m_IDProgram, (GLuint)i, bufSize, &length, &size, &type, name);

        printf("Uniform #%d Type: 0x%x Name: %s\n", i, type, name);
    }*/

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
            LOG_ERROR << "PROGRAM::LINKING_FAILED";
            LOG_ERROR << infoLog;
        }
    }
}