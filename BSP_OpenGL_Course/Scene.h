#pragma once
#include<list>
#include<map>
#include<string>
class CGameObject;
class CLight;
class CCamera;
class CMaterial;

class CScene
{
public:
    CScene();
    //void AddGameObject();
    //void AddCamera();
    //void AddLight();
    void LoadScene();
    void Update(CCamera * pCamera);
    CCamera* GetCamera(std::string strName);
private:
    void CreateGameObjects();
    void CreateCameras();
    void CreateLights();
    void CreateMaterials();

private:
    std::list<CGameObject*> m_listGameObjects;
    std::list<CLight*> m_listLights;
    std::map<std::string, CCamera*> m_mapCameras;
    std::map<std::string, CMaterial*> m_mapMaterials;
};