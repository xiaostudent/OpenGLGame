#include "ChapterProgram2.h"

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
    -1.0f,  1.0f, 0.0f, 0.0f,1.0f,2.0f, // top left 

     1.0f,  1.0f, 0.0f, 1.0f,1.0f,3.0f, // top right
     1.0f,  0.0f, 0.0f, 1.0f,0.0f,3.0f, // bottom right
     0.0f,  0.0f, 0.0f, 0.0f,0.0f,3.0f, // bottom left
     0.0f,  1.0f, 0.0f, 0.0f,1.0f,3.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        4, 5, 7,
        5, 6, 7,
        0, 1, 3,  
        1, 2, 3,
        8, 9, 11,
        9, 10, 11
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

    glGenTextures(3, texture);

    std::string root = FileUtil::getRootPath();
    root.append("src\\2\\awesomeface.png");
    int width, height, nrChannels;
    unsigned char* data = loadPng(root, width, height, nrChannels);

    if (data) {
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        getError();
        stbi_image_free(data);
        data = NULL;
    }

    root = FileUtil::getRootPath();
    root.append("src\\2\\container.jpg");
    data = loadPng(root, width, height, nrChannels);

    if (data) {
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        getError();
        stbi_image_free(data);
        data = NULL;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    unsigned int size;
    root = FileUtil::getRootPath();
    root.append("src\\2\\awesomeface.pkm");
    data = loadKTX(root, width, height, size); //需要Y轴翻转

    if (data) {
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA8_ETC2_EAC, width, height, 0, size - 16, (data + 16)); //要判断扩展是否支持
        delete(data);
    }


    textureUnti = getUniformLocation("texture2");
    glUniform1i(textureUnti, 5);
    textureUnti = getUniformLocation("texture1");
    glUniform1i(textureUnti, 4);
    textureUnti = getUniformLocation("texture3");
    glUniform1i(textureUnti, 6);

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
        glActiveTexture(GL_TEXTURE0 + 6);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,(void*)0);
    }
}


unsigned char* ChapterProgram2::loadPng(string path,int& width,int&height,int& nrChannels) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    return data;
}


unsigned char* ChapterProgram2::loadKTX(string path, int& width, int& height, unsigned int& size) {
    FILE* fp = 0;
    fopen_s(&fp, path.c_str(), "rb");
    if (fp == NULL)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    short order = 0x0401;
    if (((char*)(&order))[0] == 4 && ((char*)(&order))[1] == 1) {
        printf("大端序\n");
    }
    else if (((char*)(&order))[0] == 1 && ((char*)(&order))[1] == 4) {  //高字节保存在内存的高地址
        printf("小端序\n");
    }

    unsigned char* buffer = (unsigned char*)malloc(size);

    int bytesRead;
    bytesRead = fread(buffer, size, 1, fp);

    //文件为大端序保存
    width = buffer[12] * 256 + buffer[13];
    height = buffer[14] * 256 + buffer[15];


    return buffer;

}