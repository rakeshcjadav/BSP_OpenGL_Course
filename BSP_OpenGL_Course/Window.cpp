#include"pch.h"
#include"Window.h"
#include"Viewport.h"
#include"Camera.h"
#include"CameraController.h"
#include"Scene.h"


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
	CAssetManager::Destroy();
	glfwTerminate();
	delete m_pViewport;
}

bool CWindow::Init(int width, int height, std::string strName)
{
	// OpenGL 3.3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
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
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_MULTISAMPLE);

	CAssetManager::Init();

	m_pViewport = new CViewport(0, 0, width, height);
	//m_pViewport2 = new CViewport(width/2, 0, width/2, height);
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

	//CCamera* pCamera2 = m_pScene->GetCamera("SecondCamera");
	//m_pViewport2->Clear(glm::vec4(0.2f, 0.0f, 0.2f, 1.0f));
	//m_pViewport2->Update(pCamera);

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