#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gui/Gui.hpp"

class Window
{
private:
    GLFWwindow* window;
    Gui* gui;

    int width;
    int height;
    const char* title;

public:
    Window() = default;
    bool initialize(int width, int height, const char* title);
    ~Window();
    void shutdown();

    void update();
    void render();
};
