#include "ChapterProgram2.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

ChapterProgram2::ChapterProgram2() :GLProgram()
{
    std::string root = FileUtil::getRootPath();
    std::string root2 = root;
    root.append("src\\2\\2.vert");
    root2.append("src\\2\\2.frag");
    std::string vertfile = FileUtil::getFileString(root);
    std::string fragfile = FileUtil::getFileString(root2);
    loadShaderString(vertfile, fragfile);
    init();
}


bool ChapterProgram2::init() {
    float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f,1.0f,1.0f, // top right
     0.5f, -0.5f, 0.0f, 1.0f,0.0f,1.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f,0.0f,1.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f,1.0f,1.0f, // top left 

     1.0f,  1.0f, 0.0f, 1.0f,1.0f,2.0f, // top right
     1.0f, -1.0f, 0.0f, 1.0f,0.0f,2.0f, // bottom right
    -1.0f, -1.0f, 0.0f, 0.0f,0.0f,2.0f, // bottom left
    -1.0f,  1.0f, 0.0f, 0.0f,1.0f,2.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        4, 5, 7,
        5, 6, 7,
        0, 1, 3,  
        1, 2, 3   
    };

    glGenVertexArrays(1, VAO);

    glBindVertexArray(VAO[0]);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int v_aPos = getAttribLocation("aPos");
    glEnableVertexAttribArray(v_aPos);
    glVertexAttribPointer(v_aPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);


    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3 * sizeof(float)));


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    std::string root = FileUtil::getRootPath();
    root.append("src\\2\\awesomeface.png");
    int width, height, nrChannels;
    unsigned char* data = loadPng(root, width, height, nrChannels);

    if (data) {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        getError();
        stbi_image_free(data);
        data = NULL;
    }

    textureUnti = getUniformLocation("texture2");
    glUniform1i(textureUnti, 5);

    root = FileUtil::getRootPath();
    root.append("src\\2\\container.jpg");
    data = loadPng(root, width, height, nrChannels);

    if (data) {
        glGenTextures(1, texture + 1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        getError();
        stbi_image_free(data);
    }

    textureUnti = getUniformLocation("texture1");
    glUniform1i(textureUnti, 4);
    getError();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}



void ChapterProgram2::render() {
    if (useProgram()) {
        getError();
        glBindVertexArray(VAO[0]);
        glActiveTexture(GL_TEXTURE0 + 4);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glActiveTexture(GL_TEXTURE0 + 5);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT,(void*)0);
    }
}


unsigned char* ChapterProgram2::loadPng(string path,int& width,int&height,int& nrChannels) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    return data;
}