#include "Log.h"
#include "OpenGL.h"
#include <stdio.h>
#include <string>
#include <format>
#include "WinUtils.h"
#include "Program.h"
#include "GLM.h"
#include "Texture.h"
#include <vector>
#include"Mesh.h"
#include"Camera.h"
#include"Viewport.h"
#include"Window.h"

unsigned int CreateMeshUsingVBO(int& indexCount);
CMesh * CreateMeshUsingVBOnEBO();
void RenderMesh_Elements(
    CMesh * pMesh, 
    CProgram * pProgram, CTexture * pTextureOne, 
    CTexture * pTextureTwo, CCamera * pCamera,
    bool bWireframe, float* color);
void RenderMesh_Arrays(unsigned int meshID, int vertexCount, unsigned int programID, float* color);

void KeyCallBack(GLFWwindow * pWindow, int key, int scancode, int action, int mod)
{
    LogMessage(std::format("Key Input : {0} {1} {2} {3}", key, scancode, action, mod));
}

void CharCallBack(GLFWwindow* pWindow, unsigned int character)
{
    LogMessage(std::format("Char Input : {0}", character));
} 


int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return false;

    CWindow* pWindow = CWindow::Create(640, 480, "Hello World");
    pWindow->CreateScene();

    CWindow* pWindow2 = CWindow::Create(500, 500, "Hello World 2");
    pWindow2->CreateScene();


    while(1)
    {
        if (pWindow->IsWindowClosed() || pWindow2->IsWindowClosed())
            break;

        if (!pWindow->IsWindowClosed())
        {
            pWindow->MakeCurrent();
            pWindow->RenderOneFrame();
        }
        
        if (!pWindow2->IsWindowClosed())
        {
            pWindow2->MakeCurrent();
            pWindow2->RenderOneFrame();
        }
    }
   
    //glfwSetCharCallback(window, CharCallBack);
    delete pWindow;
    delete pWindow2;
	return 0;
}