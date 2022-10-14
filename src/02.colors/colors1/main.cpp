#include <iostream>
#include <math.h>
#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../shader.h"


const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

// layout: pos:vec3,uv:vec2,normal:vec3
float cubeVertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
};

struct Input {
    glm::vec2 inputAxis;
    bool shiftPressed;
};

void onWindowSizeChanged(GLFWwindow* window, int width, int height){
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    std::cout << "Changed window size: " << width << "; " << height << std::endl;
}
Input getInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    Input input;
    input.inputAxis = glm::vec2(0.0f, 0.0f);
    input.shiftPressed = false;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        input.shiftPressed = true;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        input.inputAxis.y = 1;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        input.inputAxis.y = -1;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        input.inputAxis.x = -1;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        input.inputAxis.x = 1;

    return input;
}

int main() {
    if (!glfwInit()) {
        std::cout << "Couldn't intitialize glfw" <<  std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpengGL Colors", NULL, NULL);
    if (window == NULL) {
        std::cout << "Couldn't initialize glfw Window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD Couldn't load methods!" << std::endl;
        glfwTerminate();
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);

    glm::vec3 positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
    };

    uint VBO, VAO, lightVAO;

    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("./src/02.colors/colors1/shaders/basic.vs", "./src/02.colors/colors1/shaders/basic.fs");
    Shader shaderLightObject("./src/02.colors/colors1/shaders/basic_light.vs", "./src/02.colors/colors1/shaders/basic_light.fs");

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        // time
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // input
        Input input = getInput(window);

        // params
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightPosition = glm::vec3(3.0f,  0.0f,  0.0f);

        // math
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));        
        projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render cubes
        lightingShader.use();
        glBindVertexArray(VAO);
        for (int i = 0, n = sizeof(positions) / sizeof(*positions); i < n; i++) {
            float angle = currentFrameTime * glm::radians(20.0f);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            model = glm::scale(model, glm::vec3(1.0f));
            model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.5f));
            
            lightingShader.setMat4("model", model);
            lightingShader.setMat4("view", view);
            lightingShader.setMat4("projection", projection);
            
            lightingShader.setVec3f("objectColor", glm::vec3(1.0f, 1.0f, 0.2f));
            lightingShader.setVec3f("lightColor", lightColor);
            lightingShader.setVec3f("lightPos", lightPosition);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0); // no need to unbind it every time but ok

        // render light-cube
        shaderLightObject.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.25f));
        model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        shaderLightObject.setMat4("model", model);
        shaderLightObject.setMat4("view", view);
        shaderLightObject.setMat4("projection", projection);
        shaderLightObject.setVec3f("lightColor", lightColor);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0); // no need to unbind it every time but ok

        // events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}