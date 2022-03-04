#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = -90.0, float _pitch = 0.0);
	void processInput(GLFWwindow* window);
	glm::mat4 GetProjectionViewMatrix();
	void setCurrentFrame(float);
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void setWorldUp(glm::vec3);

	void setPerspective(float zoom=45, float width=800, float height=600, float near=0.1, float far=100);
	
private:
	void updatePerspective();
	void updateCameraVectors();

	//视图矩阵相关
	//下面四个组成相机坐标系
	glm::vec3 pos=glm::vec3(0.0f, 0.0f, 0.0f);  //相机位置
	glm::vec3 front= glm::vec3(0.0f, 0.0f, -1.0f);  //相机朝向
	glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f);   //相机向上向量
	glm::vec3 right;   //相机向右向量

	glm::vec3 worldUp= glm::vec3(0.0f, 1.0f, 0.0f);  //相机世界坐标向上向量
	float _currFrame = 0;
	float _lastFrame = 0;
	float _deltaTime = 0;

	float lastX;
	float lastY;

	float yaw = -90.0f;	
	float pitch = 0.0f;

	//投影矩阵相关
	glm::mat4 projection;
	float _near=0.1;
	float _far=100.0;
	float _width = 800;
	float _height = 600;
	float _zoom = 45;
};


#endif // !CAMERA_H

