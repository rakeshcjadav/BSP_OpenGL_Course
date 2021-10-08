#pragma once

class CMesh;
class CMaterial;
struct SMeshData;

class CModel
{
public:
	CModel(std::list<SMeshData*> & listMeshdata, const CMaterial* pMaterial);
	const CMaterial* GetMaterial() const;
	void SetMaterial(const CMaterial* pMaterial);
	void Render() const;
private:
	std::list<CMesh*> m_listMeshes;
	const CMaterial* m_pMaterial;
};