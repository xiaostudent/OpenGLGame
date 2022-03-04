#include "src/main.h"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "src/base/FileUtil.h"
#include <windows.h>
#include "src/1/ChapterProgram1.h"
#include "src/2/ChapterProgram2.h"
#include "src/3/ChapterProgram3.h"
#include "src/base/Camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
GLProgram* program;

float currentFrame = 0.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (program) program->scroll_callback(window, xoffset, yoffset);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (program) program->mouse_callback( window,xposIn,yposIn);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (program) program->processInput(window);
}

void initShaderProgram() {
   program=(GLProgram*)new ChapterProgram3();
}

void render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
    if (program) {
        program->render();
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    initShaderProgram();

    while (!glfwWindowShouldClose(window))
    {
        currentFrame = static_cast<float>(glfwGetTime());
        if (program) program->update(currentFrame);
        processInput(window);
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if (program) {
        delete program;
        program = NULL;
    }
    glfwTerminate();
    return 0;
}