#include "../../include/imgui/imgui.h"
#include "../../include/imgui/imgui_impl_glfw.h"
#include "../../include/imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <math.h>
#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../Shader.h"


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
    // setup glfw
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

    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    
    // setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);

    // application
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

    Shader lightingShader("./src/02.colors/colors3/shaders/basic.vs", "./src/02.colors/colors3/shaders/basic.fs");
    Shader shaderLightObject("./src/02.colors/colors3/shaders/basic_light.vs", "./src/02.colors/colors3/shaders/basic_light.fs");

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    bool isPaused = false;
    bool isDiscoMode = false;
    glm::vec3 lightStartPosition = glm::vec3(0.0f,  0.0f,  0.0f);

    // uniform inputs
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 ambient, diffuse, specular, lightAmbient, lightDiffuse, lightSpecular;
    float shininess = 32.0f;
    ambient = glm::vec3(0.1f,0.1f,0.1f);
    diffuse = glm::vec3(0.5f,0.1f,0.5f);
    specular = glm::vec3(0.5f,0.5f,0.1f);
    lightAmbient = glm::vec3(0.1f,0.1f,0.1f);
    lightDiffuse = glm::vec3(0.5f,0.5f,0.5f);
    lightSpecular = glm::vec3(1.0f,1.0f,1.0f);

    while(!glfwWindowShouldClose(window)) {
        // time
        float currentFrameTime = 0.0f;
        if (isPaused) {
            currentFrameTime = lastFrameTime;
        } else {
            currentFrameTime = glfwGetTime();
        }
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // input
        Input input = getInput(window);

        // params
        float sinPos = sin(currentFrameTime) * 1.5f;
        float cosPos = cos(currentFrameTime) * 1.5f;
        glm::vec3 lightPosition = lightStartPosition + glm::vec3(sinPos, 0.0f, cosPos);

        // math
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, -6.0f);
        view = glm::translate(view, viewPos);        
        projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        
        glm::vec3 lightPositionVS = view * glm::vec4(lightPosition, 1.0f);

        if (isDiscoMode) {
            lightColor.x = sin(currentFrameTime) * 2.0f;
            lightColor.y = sin(currentFrameTime) * 0.7f;
            lightColor.z = sin(currentFrameTime) * 1.3f;
        }

        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

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
            
            lightingShader.setVec3f("light.ambient", lightAmbient * lightColor * 0.2f);
            lightingShader.setVec3f("light.diffuse", lightDiffuse * lightColor);
            lightingShader.setVec3f("light.specular", lightSpecular);
            lightingShader.setVec3f("light.positionVS", lightPositionVS);

            lightingShader.setVec3f("material.ambient", ambient);
            lightingShader.setVec3f("material.diffuse", diffuse);
            lightingShader.setVec3f("material.specular", specular);
            lightingShader.setFloat("material.shininess", shininess);

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

        // imgui
        ImGui::Begin("Lighting Settings");
        ImGui::Checkbox("Pause", &isPaused);
        ImGui::Text("Light Properties:");
        ImGui::Checkbox("Disco Light", &isDiscoMode);
        ImGui::SliderFloat3("Light Ambient", (float*)&lightAmbient, 0.0f, 1.0f);
        ImGui::SliderFloat3("Light Diffuse", (float*)&lightDiffuse, 0.0f, 1.0f);
        ImGui::SliderFloat3("Light Specular", (float*)&lightSpecular, 0.0f, 1.0f);
        ImGui::ColorPicker3("Light Color", (float*)&lightColor, ImGuiColorEditFlags_DisplayRGB);
        ImGui::End();
        
        ImGui::Begin("Material Settings");
        ImGui::SliderFloat3("Ambient", (float*)&ambient, 0.0f, 1.0f);
        ImGui::SliderFloat3("Diffuse",  (float*)&diffuse, 0.0f, 1.0f);
        ImGui::SliderFloat3("Specular",  (float*)&specular, 0.0f, 1.0f);
        ImGui::SliderFloat("Specular Factor", &shininess, 8.0f, 2048.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}