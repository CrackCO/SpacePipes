#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class Window
{
private:
    GLFWwindow* window;
    ImGuiContext* imguiContext;

    int width;
    int height;
    const char* title;

public:
    Window(int width, int height, const char* title);
    ~Window();

    bool initialize();
    void update();
    void render();
    void shutdown();
};