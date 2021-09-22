#include"Material.h"
#include"Texture.h"
#include"Program.h"
#include"OpenGL.h"

CMaterial::CMaterial(std::string strName, BlendType blendType, SMaterialProperties * pProperties, CProgram* pProgram, std::list<CTexture*> listTextures)
{
    m_strName = strName;
    m_blendType = blendType;
    m_pProperties = pProperties;
    m_pProgram = pProgram;
    m_listTextures = listTextures;
}

void CMaterial::Bind()
{
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    if (m_blendType == BlendType::OPAQUE)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
    }
    else if (m_blendType == BlendType::TRANSPARENT)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tranparent blend or Alpha blend or Tranparent
    }
    unsigned int i = 0;
    for (CTexture* pTexture : m_listTextures)
    {
        pTexture->Bind(i++);
    }
    m_pProgram->Use();

    m_pProgram->SetUniform("DiffuseTex", 0);
    m_pProgram->SetUniform("SpecularTex", 1);

    if (m_pProperties)
    {
        m_pProgram->SetUniform("material.uAmbientColor", m_pProperties->colorAmbient);
        m_pProgram->SetUniform("material.uDiffuseColor", m_pProperties->colorDiffuse);
        m_pProgram->SetUniform("material.uSpecularColor", m_pProperties->colorSpecular);
        m_pProgram->SetUniform("material.uSpecularStrength", m_pProperties->fSpecularStrength);
        m_pProgram->SetUniform("material.uShininess", m_pProperties->fShininess);
    }
}

void CMaterial::SetUniform(std::string name, int value)
{
    m_pProgram->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, float value)
{
    m_pProgram->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, glm::vec3& value)
{
    m_pProgram->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, glm::vec4& value)
{
    m_pProgram->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, glm::mat4& value)
{
    m_pProgram->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, float* value)
{
    m_pProgram->SetUniform(name, value);
}