#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "gui/Gui.hpp"


class Window
{
public:
    Window(int width, int height, const char* title);

    void Shutdown();
    void Run();
    // void render();
    bool IsReady() const;

    ~Window();

private:
    void SetCallbacks();

private:
    GLFWwindow* window = nullptr;

    std::unique_ptr<Gui> gui;

    int width = 0;
    int height = 0;
    std::string title;
};
