#include "Window.hpp"

#include "renderer/Renderer.hpp"
#include "scene/World.hpp"
#include "scene/Camera.hpp"

#include "gui/Gui.hpp"

bool leftMouseButtonPressed = false;
bool newMove = false;
float lastX = 400, lastY = 300;
float mouseSensitivity = 0.5f;
glm::vec4 clearColor = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);

Camera camera(
    glm::vec3(0.0f, 0.0f, 0.0f), 
    4.0f, 
    45.0f, 
    45.0f,

    45.0f, 
    800.0f / 600.0f, 
    0.1f, 
    100.0f
);

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void charCallback(GLFWwindow* window, unsigned int c);


bool Window::initialize(int width, int height, const char* title)
{
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        shutdown();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    // glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize OpenGL loader\n");
        shutdown();
        return false;
    }

    gui->initialize(window);

    return true;
}


Window::~Window()
{
    shutdown();
}


void Window::update()
{
    /* for skeletal render  */
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, charCallback);


    Renderer renderer(window, Scene(World(), camera));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.render();

        gui->render();

        glfwSwapBuffers(window);

        /* for camera rotation */
        // camera.setYaw(glfwGetTime() * 10.0f);
    }
}

void Window::shutdown()
{
    gui->shutdown();

    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

    if (leftMouseButtonPressed) {
        if (newMove) {
            lastX = xpos;
            lastY = ypos;
            newMove = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        camera.setYaw(camera.getYaw() + xoffset);
        camera.setPitch(camera.getPitch() + yoffset);

        if (camera.getPitch() > 89.0f) camera.setPitch(89.0f);
        if (camera.getPitch() < -89.0f) camera.setPitch(-89.0f);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            leftMouseButtonPressed = true;
            newMove = true;
        } else if (action == GLFW_RELEASE) {
            leftMouseButtonPressed = false;
        }
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

    camera.setDist(camera.getDist() - yoffset * mouseSensitivity);
    
    if (camera.getDist() < 2.0f) camera.setDist(2.0f);
    if (camera.getDist() > 20.0f) camera.setDist(20.0f);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void charCallback(GLFWwindow* window, unsigned int c) {
    ImGui_ImplGlfw_CharCallback(window, c);
}