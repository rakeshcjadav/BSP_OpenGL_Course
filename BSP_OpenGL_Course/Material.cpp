#include"Material.h"
#include"Texture.h"
#include"Program.h"
#include"OpenGL.h"

CMaterial::CMaterial(std::string strName, SMaterialRenderStates* pStates, SMaterialProperties * pProperties, CProgram* pProgram, std::map<std::string, CTexture*> mapTextures)
{
    m_strName = strName;
    m_pStates = pStates;
    m_pProperties = pProperties;
    m_pProgram = pProgram;
    m_mapTextures = mapTextures;
}

void CMaterial::Bind()
{
    SetMaterialStates();

    m_pProgram->Use();

    int i = 0;
    for (auto itr = m_mapTextures.begin(); itr != m_mapTextures.end(); itr++)
    {
        std::string uniformName = itr->first;
        CTexture* pTexture = itr->second;
        pTexture->Bind(i);
        m_pProgram->SetUniform(uniformName, i);
        i++;
    }

    SetMaterialProperties();
}

void CMaterial::SetMaterialStates()
{
    if (m_pStates->DepthTest)
        glEnable(GL_DEPTH_TEST);
    if (m_pStates->CullFace)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(static_cast<int>(m_pStates->Face));
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
    if (m_pStates->BlendType == SMaterialRenderStates::BLEND_TYPE::OPAQUE)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
    }
    else if (m_pStates->BlendType == SMaterialRenderStates::BLEND_TYPE::TRANSPARENT)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tranparent blend or Alpha blend or Tranparent
    }
}

void CMaterial::SetMaterialProperties()
{
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