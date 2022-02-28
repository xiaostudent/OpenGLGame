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
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, VAO);

    glBindVertexArray(VAO[0]);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int v_aPos = getAttribLocation("aPos");
    glEnableVertexAttribArray(v_aPos);
    glVertexAttribPointer(v_aPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    getError();

    
    return true;
}



void ChapterProgram2::render() {
    if (useProgram()) {
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}


void ChapterProgram2::loadPng() {

}