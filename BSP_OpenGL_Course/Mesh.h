#pragma once
#include "GLM.h"
#include<vector>

// Forward declarations
struct SVertex;
struct SMeshData;

class CMesh
{
public:
	CMesh(const SMeshData * pData);
    void Bind();
    void UnBind();
    void Render();
private:
	void LoadMesh(const SMeshData * pData);
private:
	unsigned int m_IDMesh;
    unsigned int m_iIndexCount;
};


struct SVertex
{
    glm::vec3 position;
    glm::vec2 uv;

    SVertex(glm::vec3 _pos, glm::vec2 _uv)
    {
        position = _pos;
        uv = _uv;
    }
};

struct SMeshData
{
    std::vector<SVertex> aVertices;
    std::vector<unsigned int> aIndices;
};
