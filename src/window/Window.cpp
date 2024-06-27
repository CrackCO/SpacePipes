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


Window::Window(int width, int height, const char* title)
{
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        Shutdown();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    // glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize OpenGL loader\n");
        Shutdown();
        return;
    }

    gui = std::make_unique<Gui>();
    gui->Initialize(window);

    SetCallbacks();
}


Window::~Window()
{ Shutdown(); }


void Window::Run()
{
    /* for skeletal render  */
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    Renderer renderer(window, Scene(World(), camera));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Render();

        gui->Render();

        glfwSwapBuffers(window);
    }
}

void Window::Shutdown()
{
    gui->Shutdown();
    gui = nullptr;

    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}

bool Window::IsReady() const
{ return (window != nullptr) && (gui != nullptr); }


void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


void Window::SetCallbacks()
{
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });


    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int c) {
        ImGui_ImplGlfw_CharCallback(window, c);
    });
}


// -------------- GLFW callbacks --------------
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

        camera.SetYaw(camera.GetYaw() + xoffset);
        camera.SetPitch(camera.GetPitch() + yoffset);

        if (camera.GetPitch() > 89.0f) camera.SetPitch(89.0f);
        if (camera.GetPitch() < -89.0f) camera.SetPitch(-89.0f);
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

    camera.SetDist(camera.GetDist() - yoffset * mouseSensitivity);

    if (camera.GetDist() < 2.0f) camera.SetDist(2.0f);
    if (camera.GetDist() > 20.0f) camera.SetDist(20.0f);
}
