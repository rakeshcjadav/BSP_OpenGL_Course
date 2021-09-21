#pragma once
#include "GLM.h"
#include<vector>

// Forward declarations
struct SVertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;

    SVertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec2 _uv)
    {
        position = _pos;
        normal = _normal;
        uv = _uv;
    }
};
struct SMeshData
{
    enum class MESHTYPE
    {
        TRIANGLES = 0,
        TRIANGLE_FAN,
        LINES
    };
    std::vector<SVertex> aVertices;
    std::vector<unsigned int> aIndices;
    MESHTYPE type = MESHTYPE::TRIANGLES;
};

class CMesh
{
public:
    static CMesh* CreatePlane();
    static CMesh * CreateCube();
    static CMesh* CreateRectangle();
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
    SMeshData::MESHTYPE m_meshType;
};





