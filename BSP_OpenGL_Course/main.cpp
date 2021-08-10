#include "Log.h"
#include "OpenGL.h"
#include <stdio.h>
#include <string>
#include <format>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "WinUtils.h"
#include "Program.h"
#include "GLM.h"

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

unsigned int CreateMeshUsingVBO(int& indexCount);
unsigned int CreateMeshUsingVBOnEBO(int & indexCount);
unsigned int LoadTexture(std::string strTextureName, std::string extension);
void RenderMesh_Elements(
    unsigned int meshID, int indexCount, 
    CProgram * pProgram, unsigned int textureID, 
    unsigned int secondTextureID,
    bool bWireframe, float* color);
void RenderMesh_Arrays(unsigned int meshID, int vertexCount, unsigned int programID, float* color);

int main()
{
    /*
    //glm::mat4 cameraMat = camera(1.0f, glm::vec2(2.0f, 1.0f));
    glm::mat4 identityMat = glm::identity<glm::mat4>();
    //glm::mat4 scaleMat = glm::scale(identityMat, glm::vec3(2.0f, 1.0f, 1.0f));
    //LogMessage("Scale: " + glm::to_string(scaleMat));

   // glm::mat4 translateMat = glm::translate(identityMat, glm::vec3(5.0f, 0.0f, 0.0f));
    //LogMessage("Translation: " + glm::to_string(translateMat));

    glm::mat4 rotationMat = glm::rotate(identityMat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    LogMessage("Rotation: " + glm::to_string(rotationMat));

    glm::vec4 point0(2.0f, 2.0f, 0.0f, 0.0f);
    glm::vec4 point1(-2.0f, 2.0f, 0.0f, 0.0f);
    glm::vec4 point2(2.0f, -2.0f, 0.0f, 0.0f);
    glm::vec4 point3(-2.0f, -2.0f, 0.0f, 0.0f);
    //LogMessage("Point : " + glm::to_string(point));
    glm::vec4 newpoint0 = rotationMat * point0;
    glm::vec4 newpoint1 = rotationMat * point1;
    glm::vec4 newpoint2 = rotationMat * point2;
    glm::vec4 newpoint3 = rotationMat * point3;
    LogMessage("Transformed Point0 : " + glm::to_string(newpoint0));
    LogMessage("Transformed Point1 : " + glm::to_string(newpoint1));
    LogMessage("Transformed Point2 : " + glm::to_string(newpoint2));
    LogMessage("Transformed Point3 : " + glm::to_string(newpoint3));
    */

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

    int indexCount;
    unsigned int mesh = CreateMeshUsingVBOnEBO(indexCount);
   // unsigned int program = CreateShaders();

    int vertexCount;
    unsigned int arrayMesh = CreateMeshUsingVBO(vertexCount);

    unsigned int texture = LoadTexture("minion-transparent-background-9.png", "jpg");
    LogMessage(std::format("Texture iD : {0}", texture));

    unsigned int texture2 = LoadTexture("minion.jpg", "jpg");

    CProgram* pProgram = new CProgram("vertex_shader.vert", "fragment_shader.frag");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        float meshColor[] = {0.5f, 0.2f, 0.0f, 0.5f};
        float wireframeColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        // Render Mesh
        RenderMesh_Elements(mesh, indexCount, pProgram, texture, texture2, false, meshColor);
        RenderMesh_Elements(mesh, indexCount, pProgram, texture, texture2, true, wireframeColor);

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
    unsigned int meshID, int indexCount, 
    CProgram * pProgram, unsigned int textureID, unsigned int secondTextureID,
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

    glBindVertexArray(meshID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, secondTextureID);

    pProgram->Use();
    
    float currentTime = (float)glfwGetTime();
    float fScale = 0.1f + 1.5f *fabsf(sinf(0.05f*currentTime));

    float fSineTime = 1.0f*sinf(currentTime);

    pProgram->SetUniform("MainTex", 0);
    pProgram->SetUniform("SecondTex", 1);
    pProgram->SetUniform("Scale", fScale);
    pProgram->SetUniform("SineTime", fSineTime);
    glm::mat4 transformMat = glm::identity<glm::mat4>();
    // Order : Scale -> Rotate -> Translate
    transformMat = glm::translate(transformMat, glm::vec3(0.0f, 0.0f, 0.0f));
    transformMat = glm::rotate(transformMat, glm::radians(90.0f* fScale), glm::vec3(0.0f, 0.0f, 1.0f));
    transformMat = glm::scale(transformMat, glm::vec3(2.0f, 2.0f, 1.0f));
    pProgram->SetUniform("TransformMat", transformMat);
    pProgram->SetUniform("Color", color);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
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

unsigned int CreateMeshUsingVBOnEBO(int & indexCount)
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // 2
         -0.5f,  0.5f, 0.0f, 0.0f, 1.0f // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) /* Bytes */, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) /* Bytes */, indices, GL_STATIC_DRAW);
    }
    indexCount = sizeof(indices) / sizeof(int);
    glBindVertexArray(0);
    return VAO;
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

unsigned int LoadTexture(std::string strTextureName, std::string extension)
{
    int width, height, nrChannels;
    std::string filePath = GetTexturesPath() + strTextureName;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data == nullptr)
    {
        LogMessage(std::format("[Texture Load]: Failed to load {0} texture", filePath).c_str());
        return 0;
    }

    LogMessage(std::format(
        "[Texture Load]: {0} loaded successfully, width {1} & height {2} & channels {3}", 
        strTextureName, width, height, nrChannels).c_str());

    GLint format = GL_RGB;
    if (nrChannels > 3)
        format = GL_RGBA;


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); // 24 bits 
 
    // Texture wrapping : Default mode : REPEAT in both directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Mirrored repeat in both directions
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // Clamp to edge
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Clamp to border
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    
    
    
    // Bi-Linear Filters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Tri-Linear filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);


    //glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    return texture;
}