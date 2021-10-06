#include"pch.h"
#include"Mesh.h"

// static 
// Plane
CMesh* CMesh::CreatePlane()
{
    // Local Positions of vertices
    SMeshData meshData;
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

    meshData.aIndices = {
        0, 1, 3,
        2
    };

    meshData.type = SMeshData::MESHTYPE::TRIANGLE_STRIP;

    return new CMesh(&meshData);
}

// Circle
CMesh* CMesh::CreateCircle()
{
    // Local Positions of vertices
    SMeshData meshData;
    SVertex vertex(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.0f));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f)));
    meshData.aIndices.push_back(0);
    int circle = 360;
    int sides = 72;
    int division = circle / sides;
    for (int angle = 0, index = 1; angle <= circle; index++, angle+=division)
    {
        glm::vec3 angles(0.0f, 0.0f, angle);
        glm::mat3 mat = glm::toMat3(glm::quat(glm::radians(angles)));

        glm::vec3 pos = mat * vertex.position;
        glm::vec3 normal = mat * vertex.normal;
        glm::vec3 tex = mat * glm::vec3(vertex.uv, 1.0f);

        meshData.aVertices.push_back(SVertex(pos, normal, glm::vec2(tex)+glm::vec2(0.5f, 0.5f)));
        meshData.aIndices.push_back(index);
    }

    meshData.type = SMeshData::MESHTYPE::TRIANGLE_FAN;

    return new CMesh(&meshData);
}

// Cube
CMesh* CMesh::CreateCube()
{
    // Local Positions of vertices
    SMeshData meshData;

    std::vector<SVertex> tempVertices;
    tempVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    tempVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
    tempVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
    tempVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

    meshData.aIndices = {
        0, 1, 2,
        2, 3, 0,
    };

    std::vector<glm::vec3> angles;
    angles.push_back(glm::vec3(0.0f, 0.0f, 0.0f));  // Front
    angles.push_back(glm::vec3(-90.0f, 0.0f, 0.0f)); // Top
    angles.push_back(glm::vec3(-180.0f, 0.0f, 0.0f)); // Back
    angles.push_back(glm::vec3(-270.0f, 0.0f, 0.0f)); // Bottom
    angles.push_back(glm::vec3(0.0f, 90.0f, 0.0f)); // Left
    angles.push_back(glm::vec3(0.0f, -90.0f, 0.0f)); // Right

    int face = 0;
    int facevertex = 4;
    for (const auto & angle : angles)
    {
        glm::mat3 mat = glm::toMat3(glm::quat(glm::radians(angle)));
        for (const SVertex & vertex : tempVertices)
        {
            glm::vec3 pos = mat * vertex.position;
            glm::vec3 normal = mat * vertex.normal;
            meshData.aVertices.push_back(SVertex(pos, normal, vertex.uv));
        }
        meshData.aIndices.push_back(face * facevertex);
        meshData.aIndices.push_back(face * facevertex + 1);
        meshData.aIndices.push_back(face * facevertex + 2);
        meshData.aIndices.push_back(face * facevertex + 2);
        meshData.aIndices.push_back(face * facevertex + 3);
        meshData.aIndices.push_back(face * facevertex);
        face++;
    }

    meshData.type = SMeshData::MESHTYPE::TRIANGLES;

    return new CMesh(&meshData);
}

CMesh* CMesh::CreateRectangle()
{
    // Local Positions of vertices
    SMeshData meshData;
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

    meshData.aIndices = {
        0, 1, 2, 3
    };

    meshData.type = SMeshData::MESHTYPE::LINE_STRIP;

    return new CMesh(&meshData);
}

CMesh::CMesh(const SMeshData* pData)
{
    LoadMesh(pData);
}

void CMesh::Bind()
{
    glBindVertexArray(m_IDMesh);
}

void CMesh::UnBind()
{
    glBindVertexArray(0);
}

void CMesh::Render()
{
    glDrawElements(static_cast<int>(m_meshType), m_iIndexCount, GL_UNSIGNED_INT, nullptr);
}

void CMesh::LoadMesh(const SMeshData* pData)
{
    //LogMessage(std::format("aVertices : {0}", sizeof(SVertex) * pData->aVertices.size()));
    //LogMessage(std::format("aIndices : {0}", sizeof(unsigned int) * pData->aIndices.size()));
    
    m_meshType = pData->type;
    m_iIndexCount = pData->aIndices.size();

    glGenVertexArrays(1, &m_IDMesh);
    glBindVertexArray(m_IDMesh);
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * pData->aVertices.size() /* Bytes */, &(pData->aVertices.front()), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(2*sizeof(glm::vec3)));
        glEnableVertexAttribArray(2);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pData->aIndices.size() /* Bytes */, &(pData->aIndices.front()), GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}