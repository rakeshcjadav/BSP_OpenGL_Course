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

    delete pWindow;
    delete pWindow2;
	return 0;
}