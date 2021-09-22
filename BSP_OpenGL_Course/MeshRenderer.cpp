#include"MeshRenderer.h"
#include"Camera.h"
#include"Mesh.h"
#include"Light.h"
#include"Material.h"
#include"Transform.h"

CMeshRenderer::CMeshRenderer()
{

}

void CMeshRenderer::Render(CMesh* pMesh, CTransform* pTransform, CMaterial* pMaterial, CCamera* pCamera, std::list<CLight*> * pListLights)
{
    pMesh->Bind();
    {
        pMaterial->Bind();
        {
            float currentTime = 0.0f;// (float)glfwGetTime();
            float fScale = 0.1f + 1.5f * fabsf(sinf(0.05f * currentTime));
            float fSineTime = 1.0f * sinf(currentTime);
            
            pMaterial->SetUniform("Scale", fScale);
            pMaterial->SetUniform("SineTime", fSineTime);

            glm::mat4 transformMat = pTransform->GetTransform();
            glm::mat4 normalMat = glm::transpose(glm::inverse(transformMat));


            // Camera
            glm::mat4 cameraMat = pCamera->GetViewMatrix();
            glm::mat4 projectionMat = pCamera->GetProjectionMatrix();
            glm::vec3 cameraPos = pCamera->GetPosition();
            pMaterial->SetUniform("TransformMat", transformMat);
            pMaterial->SetUniform("NormalMat", normalMat);
            pMaterial->SetUniform("CameraMat", cameraMat);
            pMaterial->SetUniform("ProjectionMat", projectionMat);
            pMaterial->SetUniform("CameraPos", cameraPos);

            // Light
            for (CLight* pLight : *pListLights)
            {
                pLight->Bind(pMaterial);
            }
            /*
            if (pListLights)
            {
                CLight* pLight = *(pListLights->begin());
                pLight->Bind(pMaterial);
            }*/
        }
    }
    pMesh->Render();
    pMesh->UnBind();
}