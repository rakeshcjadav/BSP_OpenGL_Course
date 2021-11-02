#include"pch.h"
#include"Window.h"

int main()
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	CWindow* pWindow = CWindow::Create(1280, 720, "BSP OpenGL Course");

	while(!pWindow->IsWindowClosed())
	{
		pWindow->MakeCurrent();
		pWindow->RenderOneFrame();
	}

	delete pWindow;
	return 0;
}