#pragma once
#ifndef BASE_GLPROGRAM_H
#define BASE_GLPROGRAM_H

#include <xstring>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#include "Camera.h"

using namespace std;

class GLProgram
{
public:
	GLProgram(string,string);
	GLProgram();
	~GLProgram();
	bool useProgram();
	virtual bool init() { return true; }; //??ʼ????????
	virtual void render() {};

	unsigned int getAttribLocation(string);
	unsigned int getUniformLocation(string);

	void getError();

	Camera* getCamera() { return _camera; }
	void processInput(GLFWwindow* window);
	void update(float currFrame);
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
private:
	unsigned int createShader(string&,int);
	unsigned int createProgam();
	string _vertStr;
	string _fragStr;
	unsigned int fragmentShader;
	unsigned int vertexShader;
	unsigned int shaderProgram;
protected:
	unsigned int VBO[5];
	unsigned int VAO[5];
	unsigned int EBO[5];
	unsigned int texture[16];
	bool loadShaderString(string, string);
	unsigned int vertextCount = 0;
	Camera* _camera;
};

#endif
