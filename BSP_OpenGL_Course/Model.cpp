#include"pch.h"
#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include"Program.h"
#include"Material.h"


CModel::CModel(std::list<SMeshData*>& listMeshdata, const CMaterial* pMaterial)
{
	for (SMeshData* pMeshData : listMeshdata)
	{
		m_listMeshes.push_back(new CMesh(pMeshData));
	}
	m_pMaterial = pMaterial;
}

const CMaterial* CModel::GetMaterial() const
{
	return m_pMaterial;
}

void CModel::SetMaterial(const CMaterial* pMaterial)
{
	m_pMaterial = pMaterial;
}

void CModel::Render() const
{
	for (CMesh* pMesh : m_listMeshes)
	{
		pMesh->Bind();
		pMesh->Render();
		pMesh->UnBind();
	}
}