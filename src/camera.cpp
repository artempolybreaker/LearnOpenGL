#include <camera.h>
#include <Mesh.h>
#include <Model.h>
#include <Shader.h>

Camera::Camera() {
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
