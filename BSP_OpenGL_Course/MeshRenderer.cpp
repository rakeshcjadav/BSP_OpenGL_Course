#include"MeshRenderer.h"
#include"Camera.h"
#include"Mesh.h"
#include"Light.h"
#include"Material.h"
#include"Transform.h"

CMeshRenderer::CMeshRenderer()
{

}

void CMeshRenderer::Render(CMesh* pMesh, CTransform* pTransform, CMaterial* pMaterial, CCamera* pCamera, std::list<CLight*> listLights)
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

            // Camera
            glm::mat4 cameraMat = pCamera->GetViewMatrix();
            glm::mat4 projectionMat = pCamera->GetProjectionMatrix();
            glm::vec3 cameraPos = pCamera->GetPosition();
            pMaterial->SetUniform("TransformMat", transformMat);
            pMaterial->SetUniform("CameraMat", cameraMat);
            pMaterial->SetUniform("ProjectionMat", projectionMat);
            pMaterial->SetUniform("CameraPos", cameraPos);

            // Light
            CLight* pLight = *(listLights.begin());
            glm::vec3 lightPos = pLight->GetPosition();
            lightPos.y = fSineTime * 5.0f;
            pMaterial->SetUniform("LightPos", lightPos);
            glm::vec3 lightColor = pLight->GetColor();
            pMaterial->SetUniform("LightColor", lightColor);
        }
    }
    pMesh->Render();
    pMesh->UnBind();
}