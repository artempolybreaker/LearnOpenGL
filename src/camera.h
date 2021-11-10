#ifndef CAMERA_H
#define CAMERA_H

#include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <iostream>

const float SENSIBILITY = 5.0f;
const float MOVEMENT_SPEED = 5.0f;
const float ZOOM_SPEED = 10.0f;
const float MOVEMENT_DEAD_ZONE = 0.1f;

class Camera {
private:
    glm::vec3 camPos;
    glm::vec3 camFront;
    glm::vec3 camUp;
    glm::vec3 camRight;
    
    float fov;
    float nearPlane;
    float farPlane;
    float yaw;
    float pitch;

    glm::vec3 worldUp;

public:
    Camera(){
        camPos = glm::vec3(0.0f, 0.0f, -3.0f);
        camFront = glm::vec3(0.0f, 0.0f, -1.0f);
        worldUp = camUp = glm::vec3(0.0f, 1.0f, 0.0f);
        fov = 45.0f;
        nearPlane = 0.1f;
        farPlane = 100.0f;
        yaw = 0;
        pitch = 0;

        glm::vec3 camDir;
        camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        camDir.y = sin(glm::radians(pitch));
        camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        camFront = glm::normalize(camDir);
        camRight = glm::normalize(glm::cross(camFront, worldUp));
        camUp = glm::normalize(glm::cross(camRight, camFront));
    }

    void UpdateCameraPosition(glm::vec2 input, float deltaTime, bool shiftPressed = false) {
        float camSpeed = MOVEMENT_SPEED * deltaTime;
        if (shiftPressed)
            camSpeed *= 3;

        if (input.x > MOVEMENT_DEAD_ZONE) {
            camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
        }
        if (input.x < -MOVEMENT_DEAD_ZONE) {
            camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
        }

        if (input.y > MOVEMENT_DEAD_ZONE){
            camPos += camFront * camSpeed;
        }
        if (input.y < -MOVEMENT_DEAD_ZONE){
            camPos -= camFront * camSpeed;
        }
    }

    void UpdateCameraRotation(glm::vec2 input, float deltaTime) {
        input.x *= SENSIBILITY * deltaTime;
        input.y *= SENSIBILITY * deltaTime;

        yaw += input.x;
        pitch += input.y;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    
        glm::vec3 camDir;
        camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        camDir.y = sin(glm::radians(pitch));
        camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        camFront = glm::normalize(camDir);
        camRight = glm::normalize(glm::cross(camFront, worldUp));
        camUp = glm::normalize(glm::cross(camRight, camFront));
    }

    void UpdateCameraZoom(float input, float deltaTime) {
        float speed = ZOOM_SPEED * deltaTime;

        fov -= (float)input * speed;
        if (fov < 1.0f) fov = 1.0f;
        if (fov > 45.0f) fov = 45.0f;
    }

    glm::mat4 GetViewMat() {
        return glm::lookAt(camPos, camPos + camFront, camUp);
    }

    glm::mat4 GetProjectionMat(float ratio) {
        return glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
    }
};
#endif