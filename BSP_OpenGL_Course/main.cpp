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

unsigned int CreateMeshUsingVBO(int& indexCount);
CMesh * CreateMeshUsingVBOnEBO();
void RenderMesh_Elements(
    CMesh * pMesh, 
    CProgram * pProgram, CTexture * pTextureOne, 
    CTexture * pTextureTwo,
    bool bWireframe, float* color);
void RenderMesh_Arrays(unsigned int meshID, int vertexCount, unsigned int programID, float* color);

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int Width = 1920;
    int Height = 1080;

    // OpenGL 3.3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
    }

    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE, GL_ZERO);  // Replace blend or Opaque
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tranparent blend or Alpha blend or Tranparent
    //glEnable(GL_SCISSOR_TEST);

    glViewport(0, 0, Width, Height);

    CMesh * pMesh = CreateMeshUsingVBOnEBO();

    int vertexCount;
    unsigned int arrayMesh = CreateMeshUsingVBO(vertexCount);

    CTexture* pTexture1 = new CTexture("minion-transparent-background-9.png");
    CTexture* pTexture2 = new CTexture("minion.jpg");

    CProgram* pProgram = new CProgram("vertex_shader.vert", "fragment_shader.frag");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        float meshColor[] = {0.5f, 0.2f, 0.0f, 0.5f};
        float wireframeColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        // Render Mesh
        RenderMesh_Elements(pMesh, pProgram, pTexture1, pTexture2, false, meshColor);
        RenderMesh_Elements(pMesh, pProgram, pTexture1, pTexture2, true, wireframeColor);

        //RenderMesh_Arrays(arrayMesh, vertexCount, program, meshColor);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}

void RenderMesh_Elements(
    CMesh * pMesh, 
    CProgram * pProgram, CTexture * pTextureOne, CTexture * pTextureTwo,
    bool bWireframe, float * color)
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
        pTextureOne->Bind(0);
        pTextureTwo->Bind(1);
        pProgram->Use();
        {
            float currentTime = (float)glfwGetTime();
            float fScale = 0.1f + 1.5f * fabsf(sinf(0.05f * currentTime));
            float fSineTime = 1.0f * sinf(currentTime);

            pProgram->SetUniform("MainTex", 0);
            pProgram->SetUniform("SecondTex", 1);
            pProgram->SetUniform("Scale", fScale);
            pProgram->SetUniform("SineTime", fSineTime);
            glm::mat4 transformMat = glm::identity<glm::mat4>();
            // Order : Scale -> Rotate -> Translate
            transformMat = glm::translate(transformMat, glm::vec3(0.0f, 0.0f, 0.0f));
            transformMat = glm::rotate(transformMat, glm::radians(90.0f * fScale), glm::vec3(0.0f, 0.0f, 1.0f));
            transformMat = glm::scale(transformMat, glm::vec3(2.0f, 2.0f, 1.0f));
            pProgram->SetUniform("TransformMat", transformMat);
            pProgram->SetUniform("Color", color);
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

CMesh * CreateMeshUsingVBOnEBO()
{
    SMeshData meshData;
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)));
    meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)));

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
    vertexCount = sizeof(vertices) / (3*sizeof(float));
    glBindVertexArray(0);
    return VAO;
}
