#include "Log.h"
#include "OpenGL.h"
#include <stdio.h>
#include <string>
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

    CWindow* pWindow = CWindow::Create(1920, 1080, "Hello World");

    while(!pWindow->IsWindowClosed())
    {
        pWindow->MakeCurrent();
        pWindow->RenderOneFrame();
    }

    delete pWindow;
	return 0;
}