#include"Scene.h"
#include"Material.h"
#include"Camera.h"
#include"Light.h"
#include"GameObject.h"
#include"Texture.h"
#include"Program.h"
#include"Transform.h"
#include"Mesh.h"
#include"MeshRenderer.h"

CScene::CScene()
{

}

void CScene::Update(CCamera* pCamera)
{
    for (CGameObject* pGameObject : m_listGameObjects)
    {
        pGameObject->Update();
        pGameObject->Render(pCamera, m_listLights);
    }
}

void CScene::LoadScene()
{
    CreateMaterials();
    CreateGameObjects();
    CreateCameras();
    CreateLights();
}

CCamera* CScene::GetCamera(std::string strName)
{
    return m_mapCameras[strName];
}

void CScene::CreateGameObjects()
{
    CMeshRenderer* pMeshRenderer = new CMeshRenderer();
    CMesh* pMesh = CMesh::CreatePlane();
    // Plane
    {
        CTransform* pPlaneTransform = new CTransform();
        CGameObject* pPlane = new CGameObject(pPlaneTransform, pMesh, pMeshRenderer, m_mapMaterials["unlit_orange"]);
        m_listGameObjects.push_back(pPlane);
    }
    // Plane 2
    {
        CTransform* pPlaneTransform = new CTransform(glm::vec3(0.0f, 1.0f, 0.0f));
        CGameObject* pPlane = new CGameObject(pPlaneTransform, pMesh, pMeshRenderer, m_mapMaterials["lit_green"]);
        m_listGameObjects.push_back(pPlane);
    }
}

void CScene::CreateCameras()
{
    SCameraDef* pCameraDef = new SCameraDef();
    pCameraDef->position = glm::vec3(0.0f, 0.0f, 5.0f);
    pCameraDef->direction = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - glm::vec3(0.0f, 0.0f, 5.0f));
    pCameraDef->up = glm::vec3(0.0f, 1.0f, 0.0f);
    pCameraDef->fov = 45.0f;
    pCameraDef->fNearPlane = 0.1f;
    pCameraDef->fFarPlane = 100.0f;
    CCamera * pCamera = new CCamera(pCameraDef, nullptr);
    pCamera->SetScene(this);
    m_mapCameras["MainCamera"] = pCamera;
    CCamera* pCamera2 = new CCamera(pCameraDef, nullptr);
    pCamera2->SetScene(this);
    m_mapCameras["SecondCamera"] = pCamera2;
}

void CScene::CreateLights()
{
    m_listLights.push_back(new CLight(glm::vec3(0.0f, -2.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
}

void CScene::CreateMaterials()
{
    std::list<CTexture*> listTextures;
    listTextures.push_back(new CTexture("minion-transparent-background-9.png"));
    listTextures.push_back(new CTexture("minion.jpg"));

    CProgram* pProgramUnlit = new CProgram("unlit_vertex_shader.vert", "unlit_fragment_shader.frag");
    CProgram* pProgramLit = new CProgram("lit_vertex_shader.vert", "lit_fragment_shader.frag");

    SMaterialProperties* pOrangeProperties = new SMaterialProperties(
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(1.0f, 0.5f, 0.31f), 32.0f
    );

    SMaterialProperties* pGreenProperties = new SMaterialProperties(
        glm::vec3(0.5f, 1.0f, 0.31f),
        glm::vec3(0.5f, 1.0f, 0.31f),
        glm::vec3(0.5f, 1.0f, 0.31f), 16.0f
    );

    m_mapMaterials["unlit_orange"] = new CMaterial("unlit_orange", CMaterial::BlendType::TRANSPARENT, pOrangeProperties, pProgramUnlit, listTextures);
    m_mapMaterials["unlit_green"] = new CMaterial("unlit_green", CMaterial::BlendType::TRANSPARENT, pGreenProperties, pProgramUnlit, listTextures);
    m_mapMaterials["lit_orange"] = new CMaterial("lit_orange", CMaterial::BlendType::OPAQUE, pOrangeProperties, pProgramLit, listTextures);
    m_mapMaterials["lit_green"] = new CMaterial("lit_green", CMaterial::BlendType::OPAQUE, pGreenProperties, pProgramLit, listTextures);
}