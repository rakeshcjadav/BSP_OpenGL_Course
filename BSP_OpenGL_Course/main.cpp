#include "Log.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

unsigned int CreateMeshUsingVBO(int& indexCount);
unsigned int CreateMeshUsingVBOnEBO(int & indexCount);
unsigned int  CreateShaders();
void RenderMesh_Elements(unsigned int meshID, int indexCount, unsigned int programID, bool bWireframe, float* color);
void RenderMesh_Arrays(unsigned int meshID, int vertexCount, unsigned int programID, float* color);

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // OpenGL 3.3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
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

    glViewport(0, 0, 800, 600);

    int indexCount;
    unsigned int mesh = CreateMeshUsingVBOnEBO(indexCount);
    unsigned int program = CreateShaders();

    int vertexCount;
    unsigned int arrayMesh = CreateMeshUsingVBO(vertexCount);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        float meshColor[] = {0.5f, 0.2f, 0.0f, 0.5f};
        float wireframeColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        // Render Mesh
        RenderMesh_Elements(mesh, indexCount, program, false, meshColor);
        RenderMesh_Elements(mesh, indexCount, program, true, wireframeColor);

        RenderMesh_Arrays(arrayMesh, vertexCount, program, meshColor);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}

void RenderMesh_Elements(unsigned int meshID, int indexCount, unsigned int programID, bool bWireframe, float * color)
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
    glUseProgram(programID);
    //int SomeDataLocation = glGetUniformLocation(programID, "SomeData");
    //glUniform1f(SomeDataLocation, 0.1f);
    int ColorLocation = glGetUniformLocation(programID, "Color");
    //glUniform4f(ColorLocation, 0.5f, 0.2f, 0.0f, 1.0f);
    //float color[] = { 0.5f, 0.2f, 0.0f, 1.0f };
    glUniform4fv(ColorLocation, 1, color);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
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
        -0.5f, -0.5f, 0.0f, // 0
         0.5f, -0.5f, 0.0f, // 1
         0.5f,  0.5f, 0.0f, // 2
         -0.5f,  0.5f, 0.0f, // 3
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

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

unsigned int CreateShaders()
{
    const char* vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out float value;\n"
        "uniform vec4 Color;\n"
        "out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   value = aPos.x;\n"
        "   outColor = Color * vec4(1.0f, aPos.y+0.5f, 1.0f, 1.0);\n"
        "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    {
        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LogMessage("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
            LogMessage(infoLog);
        }
    }

    const char * fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in float value;\n"
        "//uniform vec4 Color;\n"
        "in vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = outColor;\n"
        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    {
        int  success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LogMessage("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
            LogMessage(infoLog);
        }
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    {
        int  success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            LogMessage("ERROR::PROGRAM::LINKING_FAILED");
            LogMessage(infoLog);
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}