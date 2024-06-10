#include "Renderer.hpp"

#include "iostream"
#include <cstdlib>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>


static void glCheckError(const char* operation) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error during " << operation << ": " << gluErrorString(error) << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


Renderer::Renderer(GLFWwindow* window, const World& world, const Camera& camera)
    :
    window(window),
    VAO(0), VBO(0), EBO(0),
    shaderProgram(0),
    world(world),
    camera(camera)
{
    initShaders();
    initMesh();
}

Renderer::~Renderer()
{
    cleanup();
}

GLuint Renderer::compileShader(GLuint type, const char* src)
{
    GLuint shader = glCreateShader(type); glCheckError("glCreateShader");
    glShaderSource(shader, 1, &src, nullptr); glCheckError("glShaderSource");

    glCompileShader(shader);                  glCheckError("glCompileShader");
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }

    return shader;
}


void Renderer::initShaders()
{
    const char* vertShaderSrc = R"(
        #version 330 core

        in vec3 position;

        uniform vec3 cameraPos;
        uniform vec3 cameraDir;

        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;

        uniform float time;

        out float diffuse;

        void main() {
            float angle = time * 2.0 * 3.14159;

            mat4 rotationMatrix = mat4(
                vec4(cos(angle), 0.0, sin(angle), 0.0),
                vec4(0.0, 1.0, 0.0, 0.0),
                vec4(-sin(angle), 0.0, cos(angle), 0.0),
                vec4(0.0, 0.0, 0.0, 1.0)
            );

            vec4 rotatedPosition = rotationMatrix * vec4(position, 1.0);
            vec4 viewPos = viewMatrix * rotatedPosition;
            vec3 viewDir = normalize(viewPos.xyz - cameraPos);
            diffuse = max(0.0, dot(viewDir, cameraDir));
            gl_Position = projectionMatrix * viewPos;
        }
    )";

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertShaderSrc);


    
    const char* fragShaderSrc = R"(
        #version 330 core

        out vec4 FragColor;

        in float diffuse;

        void main() {
            FragColor = vec4(diffuse, diffuse, diffuse, 1.0);
        }
    )";
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragShaderSrc);


    shaderProgram = glCreateProgram();             glCheckError("glCreateShaderProgram");
    glAttachShader(shaderProgram, vertexShader);   glCheckError("glAttachVertexShader");
    glAttachShader(shaderProgram, fragmentShader); glCheckError("glAttachFragmentShader");

    glLinkProgram(shaderProgram);                  glCheckError("glLinkShaderProgram");
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Renderer::initMesh() {
    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f
    };

    GLuint indices[] = {
        0, 1, 2, 
        2, 3, 0, 
        4, 5, 6, 
        6, 7, 4, 
        0, 4, 7, 
        7, 3, 0, 
        1, 5, 6, 
        6, 2, 1, 
        3, 2, 6, 
        6, 7, 3, 
        0, 1, 5, 
        5, 4, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::render() {
    glfwPollEvents();

    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glUniform3fv       (glGetUniformLocation( shaderProgram, "cameraPos"        ), 1,           glm::value_ptr( camera.getPos              ()));
    glUniform3fv       (glGetUniformLocation( shaderProgram, "cameraDir"        ), 1,           glm::value_ptr( camera.getDir              ()));
    glUniformMatrix4fv (glGetUniformLocation( shaderProgram, "viewMatrix"       ), 1, GL_FALSE, glm::value_ptr( camera.getViewMatrix       ()));
    glUniformMatrix4fv (glGetUniformLocation( shaderProgram, "projectionMatrix" ), 1, GL_FALSE, glm::value_ptr( camera.getProjectionMatrix ()));
    
    glUniform1f(glGetUniformLocation(shaderProgram, "time"), glfwGetTime() / 4.0f);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);

}

void Renderer::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}
