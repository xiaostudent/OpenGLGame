#include "ChapterProgram3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ChapterProgram3::ChapterProgram3() :GLProgram()
{
    std::string root = FileUtil::getRootPath();
    std::string root2 = root;
    root.append("src\\3\\3.vert");
    root2.append("src\\3\\3.frag");
    std::string vertfile = FileUtil::getFileString(root);
    std::string fragfile = FileUtil::getFileString(root2);
    loadShaderString(vertfile, fragfile);
    init();
}


bool ChapterProgram3::init() {
    _camera = new Camera();
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   //后面
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,    //前面
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   //左面
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   //右面
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   //底面
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   //顶面
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    vertextCount = sizeof(vertices) / (5 * sizeof(float));

    glGenVertexArrays(1, VAO);

    glBindVertexArray(VAO[0]);
    glGenBuffers(2, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    unsigned int v_aPos = getAttribLocation("aPos");
    glEnableVertexAttribArray(v_aPos);
    glVertexAttribPointer(v_aPos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3 * sizeof(float)));


    unsigned int offset = 0;
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float) * 10, 0, GL_STATIC_DRAW);

    float tmpBuff[160] = {0};
    for (size_t i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));


        for (size_t j = 0; j < 4; j++)
        {
            for (size_t k = 0; k < 4; k++)
            {
                tmpBuff[offset] = model[j][k];
                offset += 1;
            }
        }
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, 160 * sizeof(float), tmpBuff);

    unsigned int v_model_mat = getAttribLocation("modle_mat");
    for (size_t i = 0; i < 4; i++)
    {
        glEnableVertexAttribArray(v_model_mat+i);
        glVertexAttribPointer(v_model_mat + i, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)*i));
        glVertexAttribDivisor(v_model_mat + i, 1); //多实例，一个刷新一次
    }



    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);




    glGenTextures(2, texture);

    std::string root = FileUtil::getRootPath();
    root.append("src\\3\\awesomeface.png");
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
    root.append("src\\3\\container.jpg");
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
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    textureUnti = getUniformLocation("texture2");
    glUniform1i(textureUnti, 5);
    textureUnti = getUniformLocation("texture1");
    glUniform1i(textureUnti, 4);

    u_projection = getUniformLocation("pv");

    return true;
}

void ChapterProgram3::setPerspective() {  //设置pv矩阵
    if (_camera) {
        glm::mat4 pv = _camera->GetProjectionViewMatrix();
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, &pv[0][0]);
    }
}



void ChapterProgram3::render() {
    if (useProgram()) {
        getError();
        setPerspective();
        glBindVertexArray(VAO[0]);
        glActiveTexture(GL_TEXTURE0 + 4);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glActiveTexture(GL_TEXTURE0 + 5);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glDrawArraysInstanced(GL_TRIANGLES, 0, vertextCount, 10);  //多实例渲染
    }
}


unsigned char* ChapterProgram3::loadPng(string path,int& width,int&height,int& nrChannels) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    return data;
}