#include "Camera.h"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float _yaw, float _pitch)
{
    pos = position;
    worldUp = up;
    yaw = _yaw;
    pitch = _pitch;
    updateCameraVectors();
    updatePerspective();
}

void Camera::processInput(GLFWwindow* window) {
    float cameraSpeed = static_cast<float>(2.5 * _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += cameraSpeed * front;     //坐标向上平移
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= cameraSpeed * front;   //坐标向下平移
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= right * cameraSpeed;     //坐标向左平移
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += right * cameraSpeed;   //坐标向右平移
}

void Camera::setCurrentFrame(float currFrame) {
    _lastFrame = _currFrame;
    _currFrame = currFrame;
    _deltaTime = _currFrame - _lastFrame;
}

glm::mat4 Camera::GetProjectionViewMatrix() {
    return projection*glm::lookAt(pos, pos + front, up);
}

void Camera::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    if (abs(xoffset) > 10 || abs(yoffset) > 10) return;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::setWorldUp(glm::vec3 up) {
    worldUp = up;
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 frontTmp;
    frontTmp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontTmp.y = sin(glm::radians(pitch));
    frontTmp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontTmp);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::setPerspective(float zoom,float width,float height,float near,float far) {
    _zoom = zoom;
    _width = width;
    _height = height;
    _near = near;
    _far = far;
    updatePerspective();
}

void Camera::updatePerspective() {
    if (_height == 0) return;
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(_zoom), (float)_width / (float)_height, _near, _far);
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    _zoom -= (float)yoffset;
    if (_zoom < 1.0f)
        _zoom = 1.0f;
    if (_zoom > 45.0f)
        _zoom = 45.0f;
    updatePerspective();
}