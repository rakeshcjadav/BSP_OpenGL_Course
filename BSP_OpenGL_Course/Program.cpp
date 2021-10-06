#include"Program.h"
#include"Shader.h"
#include"OpenGL.h"
#include"Log.h"
#include"AssetManager.h"

CProgram::CProgram(std::string strVertexShaderFile, std::string strFragmentShaderFile)
{
    const CShader* pShaderVS = CAssetManager::Get().GetShader(strVertexShaderFile);
    const CShader* pShaderFS = CAssetManager::Get().GetShader(strFragmentShaderFile);

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
}

void CProgram::Use() const
{
    glUseProgram(m_IDProgram);
}

void CProgram::SetUniform(std::string name, int value) const
{
    glUniform1i(glGetUniformLocation(m_IDProgram, name.c_str()), value);
}

void CProgram::SetUniform(std::string name, float value) const
{
    glUniform1f(glGetUniformLocation(m_IDProgram, name.c_str()), value);
}

void CProgram::SetUniform(std::string name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, glm::value_ptr(value));
}

void CProgram::SetUniform(std::string name, const glm::vec4 & value) const
{
    glUniform4fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, glm::value_ptr(value));
}

void CProgram::SetUniform(std::string name, const glm::mat4 & value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void CProgram::SetUniform(std::string name, float* value) const
{
    glUniform4fv(glGetUniformLocation(m_IDProgram, name.c_str()), 1, value);
}

void CProgram::AttachShader(const CShader* pShader)
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