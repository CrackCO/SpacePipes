#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class Gui {
public:
    Gui() = default;

    bool Initialize(GLFWwindow* window);
    void Shutdown();
    void Render();

    ~Gui();
};