#include"Window.h"
#include"OpenGL.h"
#include"Viewport.h"
#include"Camera.h"
#include"Mesh.h"
#include"Texture.h"
#include"Program.h"
#include"Log.h"
#include"CameraController.h"
#include"Light.h"
#include"Material.h"
#include"Scene.h"

CMesh* CreateMeshUsingVBOnEBO()
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

unsigned int CreateMeshUsingVBO(int& vertexCount)
{
    float vertices[] = {
         0.5f, 0.5f, 0.0f, // 0
         0.9f, 0.5f, 0.0f, // 1
         0.7f,  0.9f, 0.0f  // 2
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) /* Bytes */, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    vertexCount = sizeof(vertices) / (3 * sizeof(float));
    glBindVertexArray(0);
    return VAO;
}

void RenderMesh_Elements(
    CMesh* pMesh,
    CMaterial * pMaterial, CLight * pLight, CCamera* pCamera,
    bool bWireframe, float* color)
{
    if (bWireframe)
    {
        glDisable(GL_CULL_FACE);
        glLineWidth(2.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    pMesh->Bind();
    {
        pMaterial->Bind();
        {
            float currentTime = (float)glfwGetTime();
            float fScale = 0.1f + 1.5f * fabsf(sinf(0.05f * currentTime));
            float fSineTime = 1.0f * sinf(currentTime);

            pMaterial->SetUniform("Scale", fScale);
            pMaterial->SetUniform("SineTime", fSineTime);

            // World Matrix or Model Matrix
            glm::mat4 transformMat = glm::identity<glm::mat4>();
            // Order : Scale -> Rotate -> Translate
            transformMat = glm::translate(transformMat, glm::vec3(0.0f, 0.0f, 0.0f) /* World Position of the object */);
            transformMat = glm::rotate(transformMat, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            transformMat = glm::scale(transformMat, glm::vec3(1.0f, 1.0f, 1.0f));

            // Camera
            glm::mat4 cameraMat = pCamera->GetViewMatrix();
            glm::mat4 projectionMat = pCamera->GetProjectionMatrix();
            glm::vec3 cameraPos = pCamera->GetPosition();
            pMaterial->SetUniform("TransformMat", transformMat);
            pMaterial->SetUniform("CameraMat", cameraMat);
            pMaterial->SetUniform("ProjectionMat", projectionMat);
            pMaterial->SetUniform("CameraPos", cameraPos);
            pMaterial->SetUniform("ObjectColor", color);

            // Light
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

void RenderMesh_Arrays(unsigned int meshID, int vertexCount, unsigned int programID, float* color)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glBindVertexArray(meshID);
    glUseProgram(programID);
    int ColorLocation = glGetUniformLocation(programID, "Color");
    glUniform4fv(ColorLocation, 1, color);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

std::map<GLFWwindow*, CWindow*> CWindow::s_mapWindows;

CWindow* CWindow::Create(int height, int width, std::string strName)
{
    CWindow* pWindow = new CWindow();
    if (!pWindow->Init(height, width, strName))
    {
        delete pWindow;
        pWindow = nullptr;
    }
    else
    {
        s_mapWindows[pWindow->GetGLFWWindow()] = pWindow;
    }
    return pWindow;
}

CWindow::CWindow()
{
    
}

CWindow::~CWindow()
{
    glfwTerminate();
    delete m_pViewport;
}

bool CWindow::Init(int width, int height, std::string strName)
{
    // OpenGL 3.3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    m_pWindow = glfwCreateWindow(width, height, strName.c_str(), NULL, NULL);
    if (!m_pWindow)
    {
        glfwTerminate();
        return false;
    }

    MakeCurrent();

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
        return false;
    }

    glfwSetKeyCallback(m_pWindow, CWindow::KeyCallback);
    glfwSetCursorPosCallback(m_pWindow, CWindow::CursorPosCallback);
    glfwSetScrollCallback(m_pWindow, CWindow::ScrollCallback);
    glfwSetMouseButtonCallback(m_pWindow, CWindow::MouseButtonCallback);

    // TODO: Move to material
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE, GL_ZERO);  // Replace blend or Opaque
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tranparent blend or Alpha blend or Tranparent
    glEnable(GL_SCISSOR_TEST);

    m_pViewport = new CViewport(0, 0, width, height);
    m_pViewport2 = new CViewport(width/2, 0, width/2, height);
    CreateScene();

    return true;
}

GLFWwindow* CWindow::GetGLFWWindow()
{
    return m_pWindow;
}

#pragma region CallBacks

void CWindow::KeyCallback(GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mod)
{
    if (action == GLFW_PRESS)
    {
        std::map<GLFWwindow*, CWindow*>::iterator itr = s_mapWindows.find(pGLFWWindow);
        if (itr != s_mapWindows.end())
        {
            CWindow* pWindow = itr->second;
            pWindow->NotifyKeyPressed(key, mod);
        }
    }
    else if (action == GLFW_RELEASE)
    {
        std::map<GLFWwindow*, CWindow*>::iterator itr = s_mapWindows.find(pGLFWWindow);
        if (itr != s_mapWindows.end())
        {
            CWindow* pWindow = itr->second;
            pWindow->NotifyKeyReleased(key, mod);
        }
    }
}

void CWindow::CursorPosCallback(GLFWwindow* pGLFWWindow, double xPos, double yPos)
{
    std::map<GLFWwindow*, CWindow*>::iterator itr = s_mapWindows.find(pGLFWWindow);
    if (itr != s_mapWindows.end())
    {
        CWindow* pWindow = itr->second;
        pWindow->NotifyCursorPos(xPos, yPos);
    }
}

void CWindow::ScrollCallback(GLFWwindow* pGLFWWindow, double xOffset, double yOffset)
{
    std::map<GLFWwindow*, CWindow*>::iterator itr = s_mapWindows.find(pGLFWWindow);
    if (itr != s_mapWindows.end())
    {
        CWindow* pWindow = itr->second;
        pWindow->NotifyMouseScroll(xOffset, yOffset);
    }
}

void CWindow::MouseButtonCallback(GLFWwindow* pGLFWWindow, int button, int action, int mod)
{
    std::map<GLFWwindow*, CWindow*>::iterator itr = s_mapWindows.find(pGLFWWindow);
    if (itr != s_mapWindows.end())
    {
        CWindow* pWindow = itr->second;
        pWindow->NotifyMouseButton(button, action, mod);
    }
}

void CWindow::NotifyKeyPressed(int key, int mod)
{
    for(IInputHandler * pInputHandler : m_listHandler)
    {
        pInputHandler->OnKeyPressed(key, mod);
    }
}

void CWindow::NotifyKeyReleased(int key, int mod)
{
    for (IInputHandler* pInputHandler : m_listHandler)
    {
        pInputHandler->OnKeyReleased(key, mod);
    }
}

void CWindow::NotifyCursorPos(double xPos, double yPos)
{
    for (IInputHandler* pInputHandler : m_listHandler)
    {
        pInputHandler->OnMousePos(xPos, yPos);
    }
}

void CWindow::NotifyMouseScroll(double xOffset, double yOffset)
{
    for (IInputHandler* pInputHandler : m_listHandler)
    {
        pInputHandler->OnMouseScroll(xOffset, yOffset);
    }
}

bool CWindow::IsMouseButtonDown(int button)
{
    return (glfwGetMouseButton(m_pWindow, button) == GLFW_PRESS);
}

void CWindow::NotifyMouseButton(int button, int action, int mod)
{
    for (IInputHandler* pInputHandler : m_listHandler)
    {
        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                pInputHandler->OnLeftMouseButtonDown(mod);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                pInputHandler->OnRightMouseButtonDown(mod);
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                pInputHandler->OnMiddleMouseButtonDown(mod);
                break;
            default:
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                pInputHandler->OnLeftMouseButtonUp(mod);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                pInputHandler->OnRightMouseButtonUp(mod);
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                pInputHandler->OnMiddleMouseButtonUp(mod);
                break;
            default:
                break;
            }
        }
    }
}

void CWindow::GetMousePos(double& xPos, double& yPos)
{
    //glfwGetCursorPos(m_pWin)
    glfwGetCursorPos(m_pWindow, &xPos, &yPos);
}

bool CWindow::IsKeyPressed(int key)
{
    return (GLFW_PRESS == glfwGetKey(m_pWindow, key));
}

#pragma endregion

void CWindow::CreateScene()
{
    m_pScene = new CScene();
    m_pScene->LoadScene();
    CCamera* pCamera = m_pScene->GetCamera("MainCamera");
    m_pCameraController = new CCameraController(this, pCamera);
}

void CWindow::RenderLoop()
{
    /* Loop until the user closes the window */
    while (!IsWindowClosed())
    {
        RenderOneFrame();
    }
}

bool CWindow::IsWindowClosed() const
{
    return glfwWindowShouldClose(m_pWindow);
}

void CWindow::RenderOneFrame()
{
    m_pCameraController->Update();
    CCamera* pCamera = m_pScene->GetCamera("MainCamera");
    m_pViewport->Clear(glm::vec4(0.0f, 0.0f, 0.2f, 1.0f));
    m_pViewport->Update(pCamera);

    //m_pViewport2->Clear(glm::vec4(0.2f, 0.0f, 0.2f, 1.0f));
   // m_pViewport2->Update(pCamera);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_pWindow);

    /* Poll for and process events */
    glfwPollEvents();
}

void CWindow::MakeCurrent()
{
    /* Make the window's context current */
    glfwMakeContextCurrent(m_pWindow);
}