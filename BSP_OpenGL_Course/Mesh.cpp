#include"Mesh.h"
#include"Log.h"
#include"OpenGL.h"

// static 
CMesh* CMesh::CreatePlane()
{
    // Local Positions of vertices
    SMeshData meshData;
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

    meshData.aIndices = {
        0, 1, 2,
        2, 3, 0
    };

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
    glDrawElements(GL_TRIANGLES, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
}

void CMesh::LoadMesh(const SMeshData* pData)
{
    //LogMessage(std::format("aVertices : {0}", sizeof(SVertex) * pData->aVertices.size()));
    //LogMessage(std::format("aIndices : {0}", sizeof(unsigned int) * pData->aIndices.size()));

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