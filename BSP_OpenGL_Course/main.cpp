#include "OpenGL.h"
#include <stdio.h>
#include "WinUtils.h"
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