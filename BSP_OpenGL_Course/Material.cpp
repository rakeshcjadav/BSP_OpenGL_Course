#include"pch.h"
#include"Material.h"
#include"MaterialPass.h"

CMaterial::CMaterial(std::string strName, std::vector<const CMaterialPass*> listPasses)
{
	m_strName = strName;
	m_listPasses.assign(listPasses.begin(), listPasses.end());
}

void CMaterial::Bind(unsigned int passIndex)
{
	m_iActivePass = passIndex;
}

const CMaterialPass* CMaterial::GetPass(unsigned int passIndex) const
{
	return m_listPasses[passIndex];
}

void CMaterial::SetUniform(std::string name, int value) const
{
	m_listPasses[m_iActivePass]->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, float value) const
{
	m_listPasses[m_iActivePass]->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, glm::vec3& value) const
{
	m_listPasses[m_iActivePass]->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, glm::vec4& value) const
{
	m_listPasses[m_iActivePass]->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, glm::mat4& value) const
{
	m_listPasses[m_iActivePass]->SetUniform(name, value);
}

void CMaterial::SetUniform(std::string name, float* value) const
{
	m_listPasses[m_iActivePass]->SetUniform(name, value);
}