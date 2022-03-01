#include "GLProgram.h"
#include <cstring>


GLProgram::GLProgram(string vertStr, string fragStr)
{
    shaderProgram = 0;
    vertexShader = 0;
    fragmentShader = 0;
    _vertStr = vertStr;
    _fragStr = fragStr;
    shaderProgram = createProgam();
    memset(VAO, 0, sizeof(VAO));
    memset(VBO, 0, sizeof(VBO));
    memset(EBO, 0, sizeof(EBO));
    memset(texture, 0, sizeof(texture));
}

GLProgram::GLProgram()
{
    shaderProgram = 0;
    vertexShader = 0;
    fragmentShader = 0;
    memset(VAO, 0, sizeof(VAO));
    memset(VBO, 0, sizeof(VBO));
    memset(EBO, 0, sizeof(EBO));
    memset(texture, 0, sizeof(texture));
}

bool GLProgram::loadShaderString(string vertStr, string fragStr) {
    if (shaderProgram > 0) return false;
    _vertStr = vertStr;
    _fragStr = fragStr;
    shaderProgram = createProgam();
    return true;
}



GLProgram::~GLProgram()
{
    if (vertexShader > 0) {
        glDeleteShader(vertexShader);
        vertexShader = 0;
    }
    if (fragmentShader > 0) {
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
    }

    if (shaderProgram > 0) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }

    for (size_t i = 0; i < 5; i++)
    {
        if (VAO[i] > 0) {
            glDeleteVertexArrays(1, VAO +i);
            VAO[i] = 0;
        }
        if (VBO[i] > 0) {
            glDeleteBuffers(1, VBO + i);
            VBO[i] = 0;
        }
        if (EBO[i] > 0) {
            glDeleteBuffers(1, EBO + i);
            EBO[i] = 0;
        }
    }

    for (size_t i = 0; i < 16; i++)
    {
        if (texture[i] > 0) {
            glDeleteTextures(1, texture + i);
            texture[i] = 0;
        }
    }
}

unsigned int GLProgram::createProgam() {
    if (shaderProgram > 0) return shaderProgram;
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
    memset(infoLog, '\0', 512);
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

bool GLProgram::useProgram() {
    if (shaderProgram) {
        glUseProgram(shaderProgram);
        return true;
    }
    return false;
}

unsigned int GLProgram::getAttribLocation(string name) {
    if (shaderProgram) {
        return glGetAttribLocation(shaderProgram, name.c_str());
    }
    return -1;
}

unsigned int GLProgram::getUniformLocation(string name) {
    if (shaderProgram) {
        if(useProgram())  // don't forget to activate/use the shader before setting uniforms!
        return glGetUniformLocation(shaderProgram, name.c_str());
    }
    return -1;
}


void GLProgram::getError() {
    GLenum __error = glGetError();
    if (__error) {
        printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__);
    } 
}

