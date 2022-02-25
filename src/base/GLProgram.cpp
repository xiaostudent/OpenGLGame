#include "GLProgram.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLProgram::GLProgram(string vertStr, string fragStr)
{
    _vertStr = vertStr;
    _fragStr = fragStr;
    shaderProgram = createProgam();
}

GLProgram::~GLProgram()
{
    if(vertexShader>0) glDeleteShader(vertexShader);
    if(fragmentShader > 0) glDeleteShader(fragmentShader);
}

unsigned int GLProgram::createProgam() {
    int success;
    char infoLog[512];
    vertexShader = createShader(_vertStr, GL_VERTEX_SHADER);
    fragmentShader = createShader(_fragStr, GL_FRAGMENT_SHADER);
    if (vertexShader == 0) return 0;
    if (fragmentShader == 0) return 0;
    unsigned int program = glCreateProgram();
    if (program == 0) return 0;
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
        return 0;
    }
    return program;
}

unsigned int GLProgram::createShader(string& shaderSource,int shaderType) {
    int success;
    char infoLog[512];
    unsigned int shader = glCreateShader(shaderType);
    const char* source = shaderSource.c_str();
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s\n", infoLog);
        return 0;
    }
    return shader;
}

bool 