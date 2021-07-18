#define GL_SILENCE_DEPRECATION

#include <iostream>
#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

typedef unsigned int uint;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aCol;\n"
                                 "out vec3 color;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   color = vec3(1.0, 1.0, 1.0);\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 color;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(color, 1.0f);\n"
                                   "}\0";

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

uint compileShader(int shaderType, const char *shaderSourceCode)
{
    uint shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCode, NULL);
    glCompileShader(shader);

    // check if successful
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        const char *shaderTypeStr;
        if (shaderType == GL_VERTEX_SHADER)
        {
            shaderTypeStr = "VERTEX";
        }
        else if (shaderType == GL_FRAGMENT_SHADER)
        {
            shaderTypeStr = "FRAGMENT";
        }
        else
        {
            shaderTypeStr = "UNDEFINED";
        }
        std::cout << "ERROR::SHADER::" << shaderTypeStr << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shader;
}

void linkProgram(uint shaderProgram)
{
    glLinkProgram(shaderProgram);

    // check if successful
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
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

    // compiling shaders
    uint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    uint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // linking shaders
    uint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    linkProgram(shaderProgram);

    // once linked - we don't need shader objects anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.6f, 0.5f, 0.0f,  // top l
        0.4f, 0.5f, 0.0f,   // top r
        -0.6f, -0.4f, 0.0f,
    };

    float triangles[2][9] = {
        {0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f},
        {
        -0.6f, 0.5f, 0.0f,  // top l
        0.4f, 0.5f, 0.0f,   // top r
        -0.6f, -0.4f, 0.0f,
        } // bottom left
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, meshVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // glBindVertexArray(0);
    }

    // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // glBindVertexArray(VAO);

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

    while (!glfwWindowShouldClose(window))
    {
        //INPUT
        processInput(window);

        //RENDERING
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
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