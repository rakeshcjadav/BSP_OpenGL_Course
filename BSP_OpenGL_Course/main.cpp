#include "Log.h"
#include "OpenGL.h"
#include <stdio.h>
#include <string>
//#include <fmt/format.h>
#include "WinUtils.h"
#include "Program.h"
#include "GLM.h"
#include "Texture.h"
#include <vector>
#include"Mesh.h"
#include"Camera.h"
#include"Viewport.h"
#include"Window.h"
#include"opencv2/imgcodecs.hpp"
#include"opencv2/highgui.hpp"
#include"opencv2/imgproc.hpp"

int main()
{
    
    /* Initialize the library */
    /*
    if (!glfwInit())
        return false;

    CWindow* pWindow = CWindow::Create(1920, 1080, "Hello World");
    pWindow->CreateScene();

    while(1)
    {
        if (pWindow->IsWindowClosed())
            break;

        if (!pWindow->IsWindowClosed())
        {
            pWindow->MakeCurrent();
            pWindow->RenderOneFrame();
        }
        
    }

    delete pWindow;
    */
    cv::VideoCapture cap(0);

    cv::namedWindow("Webcam", cv::WINDOW_OPENGL);
    cv::Mat img;
  //  img = cap.read(img);
    while(cap.isOpened())
    {
        img = cv::imread(GetTexturesPath() + "minion-transparent-background-9.png");
        cv::imshow("Webcam", img);
        char c = cv::waitKey(1);
        if(c == 27)
            break;
    }
    cap.release();
	return 0;
}