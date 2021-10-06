#include"pch.h"
#include"Window.h"

int main()
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	CWindow* pWindow = CWindow::Create(1920, 1080, "BSP OpenGL Course");

	while(!pWindow->IsWindowClosed())
	{
		pWindow->MakeCurrent();
		pWindow->RenderOneFrame();
	}

	delete pWindow;
	return 0;
}