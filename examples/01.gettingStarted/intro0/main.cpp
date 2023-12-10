#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

typedef unsigned int uint;

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "resized to " << width << " and " << height << std::endl;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // load OpenGL functions in runtime with help of GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.6f, 0.5f, 0.0f,  // top l
        0.4f, 0.5f, 0.0f,   // top r
        -0.6f, -0.4f, 0.0f,
    };

    float triangles[2][18] = {
        // positions            //colors
        {
        0.5f, 0.5f, 0.0f,       0.5f, 0.5f, 0.3f,
        0.5f, -0.5f, 0.0f,      1.0f, 0.5f, 0.1f,
        -0.5f, -0.5f, 0.0f,     0.5f, 0.5f, 1.0f,
        },
        {
        -0.6f, 0.5f, 0.0f,      0.2f, 0.4f, 0.2f,
        0.4f, 0.5f, 0.0f,       0.6f, 0.1f, 0.7f,
        -0.6f, -0.4f, 0.0f,     0.5f, 0.8f, 1.0f,
        }
    };

    uint indices[] = {
        0, 1, 3,
        1, 2, 3};

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
    };

    // creating vertex buffer object and vertex arrays object
    uint VBO1, VBO2, VAO1, VAO2, EBO, COLORS_VBO;

    GLuint vaos[2];
    glGenVertexArrays(2, vaos);

    GLuint vbos[2];
    glGenBuffers(2, vbos);

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &COLORS_VBO);

    for(int i = 0, n = sizeof(vaos)/sizeof(*vaos); i < n; i++) {
        GLuint vao = vaos[i];
        GLuint vbo = vbos[i];
        float* meshVertices = triangles[i];

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, meshVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);
    }

    // // set the data to the buffer
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // // tell how to intepret the vertex data (for the vertex shader)
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    // glBindBuffer(GL_ARRAY_BUFFER, COLORS_VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    // // tell how to intepret the vertex data (for the vertex shader)
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);

    // // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //std::cout << "before constructor..." << std::endl;
    std::cout << "CURRENT FOLDER: " << std::filesystem::current_path() << std::endl;
    Shader myShader("./resource/shaderVert.vs", "./resource/shaderFrag.fs");
    while (!glfwWindowShouldClose(window))
    {
        //INPUT
        processInput(window);

        //RENDERING
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        float time = glfwGetTime();
        float sinValue = sin(time) * 0.5f + 0.5f;
        myShader.setVec4f("myColor", sinValue, sinValue, 0.4f, 0.2f);
        myShader.setVec2f("offset", sin(time) * 0.5f, cos(time) * 0.5f);
        for (int i = 0; i < 2; i++)
        {
            glBindVertexArray(vaos[i]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        
        // activate the program object
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 6 );
        
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0); // no need to unbind it every time

        //EVENTS
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);
}